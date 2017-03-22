Preview :


![](https://puu.sh/u78ji/7d009c8f25.png)


#Pour cloner que cette branche

```Shell
git clone -b beta --single-branch https://github.com/eloi-duwer/rtv1.git
```



##Install
```Shell
brew install sdl2
brew install sdl2_ttf

cp ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2/SDL_ttf.h ~/.brew/Cellar/sdl2/2.0.5/include/SDL2/
cp ~/.brew/Cellar/sdl2_ttf/2.0.14/lib/* ~/.brew/Cellar/sdl2/2.0.5/lib/

```

##Si impossible d'utiliser brew :

```Shell
zsh -c "$(curl -fsSL https://raw.githubusercontent.com/kube/42homebrew/master/install.sh)"
```



##Features

* Borderless
* Fps limit
* Button lib
* Cursor changing thing
* using sdl
* threaded rendering with cpu usage limit (60tick max on all threads ( main and renderer))
* threaded raytracing (4 threads)
* volumetric fog (no godrays)
* procedural textures

##Threads

###Thread 0 -> handeling image redraws, parsing and events on main thread for easier debuging and easier code managment for the team


###Thread 1 -> pushing surface to the window (so the loading bar does not freeze)


###Thread [2-6] -> Raytracing calc