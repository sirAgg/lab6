#!/usr/bin/env python3

from os import walk

content_prefix = """#ifndef __{0}_H_
#define __{0}_H_

#include "../Model.h"
"""
content_postfix = """
#endif
"""

def gen_file(directory, out_dir, filename):
    n_points = 0
    n_lines = 0

    state = 'vertices'

    new_filename = out_dir + '/' + filename[:-4] + "_model.h"
    obj_name = filename[:-4] + "_model"
    with open(directory + '/' + filename) as obj_file:
        with open(new_filename, 'w') as c_file:
            c_file.write(content_prefix.format(obj_name.upper()) + "\n")
            c_file.write("static glm::vec3 " + obj_name + "_points[] = {\n")
            for line in obj_file.readlines():
                words = line.split()
                if words[0] == 'v':
                    c_file.write('    {' + ', '.join(words[1:]) + '},\n')
                    n_points += 1
                elif words[0] == 'l':
                    if state == 'vertices':
                        state = 'lines'
                        c_file.write('};\nstatic Line ' + obj_name +'_lines[] = {\n')
                    c_file.write( '    {' + str(int(words[1])-1) + ', ' + str(int(words[2])-1) + '},\n')
                    n_lines += 1

            if n_lines <= 0:
                c_file.write('};\nstatic Line ' + obj_name +'_lines[] = {{0,0}\n')
            c_file.write( '};\n')
            c_file.write("Model GeneratedModels::" + obj_name + " = { (glm::vec3*)&" + obj_name + "_points, " + str(n_points) + ", (Line*)&" + obj_name + "_lines, " + str(n_lines) + "};\n" + content_postfix)

    print( directory + '/' + filename + '  -->  ' + new_filename)
    return obj_name

def gen_master_files(out_dir, filename, filenames, objects):
    with open(out_dir + '/' + filename + ".cpp", "w") as master_file:
        master_file.write("#include \"" + filename + ".h\"")
        for name in filenames:
            master_file.write("\n#include \"{}\"".format(name[:-4]+"_model.h"))
    print("updated",out_dir + '/' + filename + ".cpp")

    with open(out_dir + '/' + filename + ".h", "w") as master_file:
        master_file.write("#ifndef __GEN_MODELS_H_\n#define __GEN_MODELS_H_\n#include \"../Model.h\"\nclass GeneratedModels {\npublic:\n")
        for obj in objects:
            master_file.write("static Model {};\n".format(obj))
        master_file.write("};\n#endif")
    print("updated",out_dir + '/' + filename + ".h")

if __name__ == '__main__':
    f = []
    directory = "models"
    out_directory = "src/autogen"
    for  (dirpath, dirnames, filenames) in walk(directory):
        f.extend(filenames)

    objects = []
    for filename in filenames:
        if len(filename) > 3 and ".obj" == filename[-4:]:
            objects.append(gen_file(directory, out_directory, filename))
    gen_master_files(out_directory, "generated_models", filenames, objects)
