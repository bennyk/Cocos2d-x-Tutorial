# Cocos2d-x-Tutorial

This repo contains port of popular tutorial projects (see References) to cocos2d-x v3 framework.

Following are the instructions required to build these tutorial samples: -

1. Clone the project repo and start downloading the project submodules' dependencies.
```sh
$ cd Cocos2d-x-Tutorial
$ git submodule init
$ git submodule update

$ cd cocos2d-x
$ python download-deps.py
```

### XCode

1. Launch Xcode to load the tutorial project source. In Xcode, locate any *.xcodeproj* file in *proj.ios_mac* folder to load the project. Cmd-B to build it.

### Android-Studio 

1. Issue the "cocos compile" command line to build the tutorial project.

```sh
$ cd proj.android-studio
$ cocos compile -p android --android-studio 
```
2. Launch Android-Studio, select "choose existing project" to locate any folder with *proj.android-studio*.

For a video about these steps see https://www.youtube.com/watch?v=gdOkbXYsf04 

That's all.

# REFERENCES

- Cocos2d-x tutorial for Beginners - http://www.raywenderlich.com/95835/cocos2d-x-tutorial-beginners
- Excellent "How to create a game like Tiny Wings" tutorial based on Cocos2d-iphone: -
   - http://www.raywenderlich.com/33266/how-to-create-dynamic-textures-with-ccrendertexture-in-cocos2d-2-x
   - http://www.raywenderlich.com/32954/how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-1
   - http://www.raywenderlich.com/32958/how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-2
- Other useful docs about workings of cocos2d-x renderer architecture: -
   - http://cocos2d-x.org/wiki/Detailed_explanation_of_Cocos2d-x_Multi-resolution_adaptation
   - http://www.slideshare.net/oasiskim/opengl-es-20-programming-and-cocos2dx-v33-rendering-system
   - https://github.com/plter/Cocos2d-x-js-3-docs/blob/master/Cocos2d-x/Cocos2d%20v3.0%20renderer%20pipeline%20roadmap.md


