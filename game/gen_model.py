#!/usr/bin/env python3

from os import walk

content_prefix = """
#include "../Model.h"
"""

def gen_file(directory, out_dir, filename):
    n_points = 0
    n_lines = 0

    state = 'vertices'

    new_filename = out_dir + '/' + filename[:-4] + "_model.cpp"
    obj_name = filename[:-4] + "_model"
    with open(directory + '/' + filename) as obj_file:
        with open(new_filename, 'w') as c_file:
            c_file.write(content_prefix + "\n")
            c_file.write("glm::vec3 " + obj_name + "_points[] = {\n")
            for line in obj_file.readlines():
                if line[0] == 'v':
                    c_file.write( '    {' + ', '.join(line.split()[1:]) + '},\n')
                    n_points += 1
                elif line[0] == 'l':
                    if state == 'vertices':
                        state = 'lines'
                        c_file.write('};\nLine ' + obj_name +'_lines[] = {\n')
                    words = line.split()
                    c_file.write( '    {' + str(int(words[1])-1) + ', ' + str(int(words[2])-1) + '},\n')
                    n_lines += 1

            c_file.write( '};\n')
            c_file.write("Model " + obj_name + " = { (glm::vec3*)&" + obj_name + "_points, " + str(n_points) + ", (Line*)&" + obj_name + "_lines, " + str(n_lines) + "};\n")

    print( directory + '/' + filename + '  -->  ' + new_filename)


if __name__ == '__main__':
    f = []
    directory = "models"
    out_directory = "src/autogen"
    for  (dirpath, dirnames, filenames) in walk(directory):
        f.extend(filenames)

    for filename in filenames:
        if len(filename) > 3 and ".obj" == filename[-4:]:
            gen_file(directory, out_directory, filename)
