#ifndef MOVEMGR_H
#define MOVEMGR_H

#include "lunarNXT/Receptor.h"

// Classe de gestion de déplacement
class MoveMgr : public Receptor {
private:
        // publisher donnant les ordres aux moteurs
        ros::Publisher* publisher;

        // gestion du but (rotation ou déplacement finit)
        bool hasGoal;
        float desiredLeftPosition, desiredRightPosition;
        float desiredLeftEffort, desiredRightEffort;

        // informations actuelles du moteur
        float leftPosition, rightPosition;
        float leftEffort, rightEffort;

        // donne les ordres aux moteurs
        void publish(float leftEffort, float rightEffort);
        
        // methodes verifiant si le but est atteint ou non
        void checkGoal();
        bool checkLeftGoal();
        bool checkRightGoal();

public:
        // constructeurs & destructeur
        MoveMgr();
        MoveMgr(ros::Publisher* publisher, std::string leftName, std::string rightName);
        ~MoveMgr();

        // Deplacement infinit /!\ doit etre stope manuellement
        void linearMove(float effort);
        void turnLeft(float effort);
        void turnRight(float effort);

        // deplacement finit ()avec une marge d'erreur)
        void linearMove(float effort, int cm);
        void turn(float effort, float rad);

        // coupe les moteurs
        void stop();

        // MaJ des capteurs
        void updateMotors(sensor_msgs::JointState msg);
        void updateRange(nxt_msgs::Range msg);
        
        // Getters
        float getLeftPos();
        float getRightPos();
        bool hasGoalSet();
};

#endif
