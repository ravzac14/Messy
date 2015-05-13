#ifndef MAID_H
#define MAID_H

#include "IVisibleGameObject.h"

const int WINDOW_HEIGHT = 680;
const int WINDOW_WIDTH = 920;

class Maid : public IVisibleGameObject
{
  public:
    enum ActorFace {UP,DOWN,LEFT,RIGHT};
    enum ForwardFoot {LL,LN,N,RN,RR};

    Maid();
    ~Maid();
   
    ActorFace getFace ();
    void changeFooting();
    void setFace(ActorFace f);
    bool isLegalMove(float newX, float newY);
    void move(float xOffset,float yOffset);
    void update();
    void initializeActor();
    void handleKey();

    float getVelocity() const;
    std::string getWalkAnimation ();
    std::string getIdleAnimation ();
    std::string getCleanAnimation ();
    const float MAX_VELOCITY = 10.0;
    const float WIDTH = 100.0f;
    const float HEIGHT = 100.0f;
    const std::string UP_LL = "assets/maid_animations/100x100-maid-U-LL.png";
    const std::string UP_LN = "assets/maid_animations/100x100-maid-U-LN.png";
    const std::string UP_N = "assets/maid_animations/100x100-maid-U-N.png";
    const std::string UP_RN = "assets/maid_animations/100x100-maid-U-RN.png";
    const std::string UP_RR = "assets/maid_animations/100x100-maid-U-RR.png";
    const std::string DOWN_LL = "assets/maid_animations/100x100-maid-D-LL.png";
    const std::string DOWN_LN = "assets/maid_animations/100x100-maid-D-LN.png";
    const std::string DOWN_N = "assets/maid_animations/100x100-maid-D-N.png";
    const std::string DOWN_RN = "assets/maid_animations/100x100-maid-D-RN.png";
    const std::string DOWN_RR = "assets/maid_animations/100x100-maid-D-RR.png";
    const std::string LEFT_LL = "assets/maid_animations/100x100-maid-L-DD.png";
    const std::string LEFT_LN = "assets/maid_animations/100x100-maid-L-DN.png";
    const std::string LEFT_N = "assets/maid_animations/100x100-maid-L-N.png";
    const std::string LEFT_RN = "assets/maid_animations/100x100-maid-L-UN.png";
    const std::string LEFT_RR = "assets/maid_animations/100x100-maid-L-UU.png";
    const std::string RIGHT_LL = "assets/maid_animations/100x100-maid-R-UU.png";
    const std::string RIGHT_LN = "assets/maid_animations/100x100-maid-R-UN.png";
    const std::string RIGHT_N = "assets/maid_animations/100x100-maid-R-N.png";
    const std::string RIGHT_RN = "assets/maid_animations/100x100-maid-R-DN.png";
    const std::string RIGHT_RR = "assets/maid_animations/100x100-maid-R-DD.png";
    const std::string CLEAN_0 = "assets/maid_animations/100x100-maid-clean-0and11.png";
    const std::string CLEAN_1 = "assets/maid_animations/100x100-maid-clean-1and10.png";
    const std::string CLEAN_2 = "assets/maid_animations/100x100-maid-clean-2and4and6and8.png";
    const std::string CLEAN_3 = "assets/maid_animations/100x100-maid-clean-3and7.png";
    const std::string CLEAN_4 = "assets/maid_animations/100x100-maid-clean-2and4and6and8.png";
    const std::string CLEAN_5 = "assets/maid_animations/100x100-maid-clean-5and9.png";
    const std::string CLEAN_6 = "assets/maid_animations/100x100-maid-clean-2and4and6and8.png";
    const std::string CLEAN_7 = "assets/maid_animations/100x100-maid-clean-3and7.png";
    const std::string CLEAN_8 = "assets/maid_animations/100x100-maid-clean-2and4and6and8.png";
    const std::string CLEAN_9 = "assets/maid_animations/100x100-maid-clean-5and9.png";
    const std::string CLEAN_10 = "assets/maid_animations/100x100-maid-clean-1and10.png";
    const std::string CLEAN_11 = "assets/maid_animations/100x100-maid-clean-0and11.png";
    const std::string IDLE_0 = "assets/maid_animations/100x100-maid-idle-0and5and7.png";
    const std::string IDLE_1 = "assets/maid_animations/100x100-maid-idle-1and3.png";
    const std::string IDLE_2 = "assets/maid_animations/100x100-maid-idle-2.png";
    const std::string IDLE_3 = "assets/maid_animations/100x100-maid-idle-1and3.png";
    const std::string IDLE_4 = "assets/maid_animations/100x100-maid-idle-4.png";
    const std::string IDLE_5 = "assets/maid_animations/100x100-maid-idle-0and5and7.png";
    const std::string IDLE_6 = "assets/maid_animations/100x100-maid-idle-6.png";
    const std::string IDLE_7 = "assets/maid_animations/100x100-maid-idle-0and5and7.png";
  
  private:
    ActorFace mFace;
    ForwardFoot mFoot;
    ForwardFoot mPreviousFoot;
    float mVelocity;
};

#endif
