#ifndef __LAZERSHOT_H_
#define __LAZERSHOT_H_

#include "GameObject.h"
#include "ModelShape.h"
#include "Model.h"


class LazerShot: public GameObject
{
public:
    LazerShot(Point2D pos, float speed);

    bool update(); 
    
    static const Model lazer_shot_model;

private:
    float speed;
};

#endif /* __LAZERSHOT_H_ */
