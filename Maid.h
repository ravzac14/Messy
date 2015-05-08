#ifndef MAID_H
#define MAID_H

#include "IVisibleGameObject.h"

const int WINDOW_HEIGHT = 680;
const int WINDOW_WIDTH = 920;

class Maid : public IVisibleGameObject
{
  public:
    enum ActorFace {UP,DOWN,LEFT,RIGHT};
    enum ForwardFoot {L,R};

    Maid();
    ~Maid();
   
    ActorFace getFace ();
    void setFace(ActorFace f);
    bool isLegalMove(float newX, float newY);
    void move(float xOffset,float yOffset);
    void update();
    void initializeActor();
    void handleKey();

    float getVelocity() const;
    std::string getAnimation ();
    const std::string UP_L = "assets/100x100-elephant_maid-U-L.png";
    const std::string UP_R = "assets/100x100-elephant_maid-U-R.png";
    const std::string DOWN_L = "assets/100x100-elephant_maid-D-L.png";
    const std::string DOWN_R = "assets/100x100-elephant_maid-D-R.png";
    const std::string LEFT_L = "assets/100x100-elephant_maid-L-D.png";
    const std::string LEFT_R = "assets/100x100-elephant_maid-L-U.png";
    const std::string RIGHT_L = "assets/100x100-elephant_maid-R-U.png";
    const std::string RIGHT_R = "assets/100x100-elephant_maid-R-D.png";
    const float MAX_VELOCITY = 10.0;
    const float WIDTH = 100.0f;
    const float HEIGHT = 100.0f;

  private:
    ActorFace mFace;
    ForwardFoot mFoot;
    float mVelocity;
};

#endif
