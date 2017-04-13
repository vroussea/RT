Preview :


![](https://puu.sh/u78ji/7d009c8f25.png)




##Install
```Shell
make sdl

```

##Si impossible d'utiliser brew :

```Shell
zsh -c "$(curl -fsSL https://raw.githubusercontent.com/kube/42homebrew/master/install.sh)"
```



##Features

* Borderless
* Fps limit
* Button lib to disable some effects
* Cursor changing thing
* using sdl
* threaded rendering with cpu usage limit (60tick max on all threads ( main and renderer))
* threaded raytracing (4 threads)
* volumetric fog (no godrays)
* procedural textures
* textures
* weird reflection and weird refraction

##Threads

###Thread 0 -> handeling image redraws, parsing and events on main thread for easier debuging and easier code managment for the team


###Thread 1 -> pushing surface to the window (so the loading bar does not freeze)


###Thread [2-6] -> Raytracing calc