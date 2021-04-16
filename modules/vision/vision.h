#ifndef VISION_H
#define VISION_H

#include <QMutex>

#include <modules/module.h>
#include <protobufs/packet.pb.h>

class Vision : public Module
{
public:
    /**
    *
    * Constructor for Vision objects
    *
    * @param networkAddress The address to connect into the vision network
    * @param networkPort The port to connect into the vision network
    *
    */
    Vision(QString networkAddress, quint16 networkPort);

    /**
    *
    * This method will take the upcoming vision datagrams from the network
    * and parse them to the Protocol Buffers packages
    *
    */
    void processNetworkDatagrams();

    /**
    *
    * Take the last robot detection from the vision network
    *
    * @param isYellow If the required player is from the yellow team
    * @param playerId The id of the required robot
    *
    * @return fira_message::Robot An protobuf packet class that contains all
    * robot last detection data
    */
    fira_message::Robot getLastRobotDetection(bool isYellow, int playerId);

    /**
    *
    * Take the last ball detection from the vision network
    *
    * @return fira_message::Ball An protobuf packet class that contains all
    * ball last detection data
    */
    fira_message::Ball getLastBallDetection();

    /**
    *
    * Take the last field geometry data from the network
    *
    * @return fira_message::Field An protobuf packet class that contains all
    * field geometry last detection data
    */
    fira_message::Field getLastGeometryData();

private:
    // Mutex to avoid problems with threads synchronization
    QMutex _visionMutex;

    // QMap to store the robots detections
    QMap<bool, QMap<int, fira_message::Robot>*> _robotsMap;

    // SSL_DetectionBall object to store the ball detection
    fira_message::Ball _lastBallDetection;

    // SSL_GeometryData object to sotre the last geometry detection
    fira_message::Field _lastGeometryData;

    /**
    *
    * Override for the connectToNetwork method of Module class.
    * This method bind and connects to the vision multicast interface
    *
    */
    void connectToNetwork();
};

#endif // VISION_H
