#ifndef __LAZERSHOT_H_
#define __LAZERSHOT_H_

#include "GameObject.h"
#include "Model.h"


class LazerShot: public GameObject
{
public:
    LazerShot(Point2D pos, ModelShape* shape, float speed, float stop_position);

    bool update(); 
    
    static const Model lazer_shot_model;

private:
    float speed;
    float stop_position;
};

#endif /* __LAZERSHOT_H_ */
