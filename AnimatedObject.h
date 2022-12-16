#include "BasicObject.h" // includes Graphics.hpp, using namespace sf;


class AnimatedObject : public BasicObject 
{
protected:
    AnimatedObject();
    virtual ~AnimatedObject();

    bool	        isAnimated {false};
	int	            animationStates {0};
	float	        animationCycleTimer {0};
	float	        latestAnimationUpdate {0};
    
private:

public:
    void updateAnimation(float elapsedTime);
};
