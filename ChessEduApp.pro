QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 moc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Lab14/Box2D/Collision/Shapes/b2ChainShape.cpp \
    Lab14/Box2D/Collision/Shapes/b2CircleShape.cpp \
    Lab14/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    Lab14/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    Lab14/Box2D/Collision/b2BroadPhase.cpp \
    Lab14/Box2D/Collision/b2CollideCircle.cpp \
    Lab14/Box2D/Collision/b2CollideEdge.cpp \
    Lab14/Box2D/Collision/b2CollidePolygon.cpp \
    Lab14/Box2D/Collision/b2Collision.cpp \
    Lab14/Box2D/Collision/b2Distance.cpp \
    Lab14/Box2D/Collision/b2DynamicTree.cpp \
    Lab14/Box2D/Collision/b2TimeOfImpact.cpp \
    Lab14/Box2D/Common/b2BlockAllocator.cpp \
    Lab14/Box2D/Common/b2Draw.cpp \
    Lab14/Box2D/Common/b2Math.cpp \
    Lab14/Box2D/Common/b2Settings.cpp \
    Lab14/Box2D/Common/b2StackAllocator.cpp \
    Lab14/Box2D/Common/b2Timer.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2Contact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Lab14/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    Lab14/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2Joint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    Lab14/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    Lab14/Box2D/Dynamics/b2Body.cpp \
    Lab14/Box2D/Dynamics/b2ContactManager.cpp \
    Lab14/Box2D/Dynamics/b2Fixture.cpp \
    Lab14/Box2D/Dynamics/b2Island.cpp \
    Lab14/Box2D/Dynamics/b2World.cpp \
    Lab14/Box2D/Dynamics/b2WorldCallbacks.cpp \
    Lab14/Box2D/Rope/b2Rope.cpp \
    Lab14/main.cpp \
    Lab14/mainwindow.cpp \
    chessboard.cpp \
    draggablepiece.cpp \
    foolsmate.cpp \
    main.cpp \
    startmenu.cpp

HEADERS += \
    Lab14/Box2D/Box2D.h \
    Lab14/Box2D/Collision/Shapes/b2ChainShape.h \
    Lab14/Box2D/Collision/Shapes/b2CircleShape.h \
    Lab14/Box2D/Collision/Shapes/b2EdgeShape.h \
    Lab14/Box2D/Collision/Shapes/b2PolygonShape.h \
    Lab14/Box2D/Collision/Shapes/b2Shape.h \
    Lab14/Box2D/Collision/b2BroadPhase.h \
    Lab14/Box2D/Collision/b2Collision.h \
    Lab14/Box2D/Collision/b2Distance.h \
    Lab14/Box2D/Collision/b2DynamicTree.h \
    Lab14/Box2D/Collision/b2TimeOfImpact.h \
    Lab14/Box2D/Common/b2BlockAllocator.h \
    Lab14/Box2D/Common/b2Draw.h \
    Lab14/Box2D/Common/b2GrowableStack.h \
    Lab14/Box2D/Common/b2Math.h \
    Lab14/Box2D/Common/b2Settings.h \
    Lab14/Box2D/Common/b2StackAllocator.h \
    Lab14/Box2D/Common/b2Timer.h \
    Lab14/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2CircleContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2Contact.h \
    Lab14/Box2D/Dynamics/Contacts/b2ContactSolver.h \
    Lab14/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    Lab14/Box2D/Dynamics/Contacts/b2PolygonContact.h \
    Lab14/Box2D/Dynamics/Joints/b2DistanceJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2FrictionJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2GearJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2Joint.h \
    Lab14/Box2D/Dynamics/Joints/b2MotorJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2MouseJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2PulleyJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2RopeJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2WeldJoint.h \
    Lab14/Box2D/Dynamics/Joints/b2WheelJoint.h \
    Lab14/Box2D/Dynamics/b2Body.h \
    Lab14/Box2D/Dynamics/b2ContactManager.h \
    Lab14/Box2D/Dynamics/b2Fixture.h \
    Lab14/Box2D/Dynamics/b2Island.h \
    Lab14/Box2D/Dynamics/b2TimeStep.h \
    Lab14/Box2D/Dynamics/b2World.h \
    Lab14/Box2D/Dynamics/b2WorldCallbacks.h \
    Lab14/Box2D/Rope/b2Rope.h \
    Lab14/mainwindow.h \
    chessboard.h \
    draggablepiece.h \
    foolsmate.h \
    startmenu.h

FORMS += \
    Lab14/mainwindow.ui \
    startmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    Fools-Mate.png \
    Lab14/Box2D/Box2DConfig.cmake \
    Lab14/Box2D/CMakeLists.txt \
    stockfish-windows-x86-64-sse41-popcnt.exe \
    stockfish.exe

SUBDIRS += \
    Lab14/Lab14.pro
