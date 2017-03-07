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


##Documentation

```C
void updatepixel(t_envgui *env, int x, int y, Uint32 color)
```


color int : 0x rr gg bb 
ex -> 0xffffff = 255 255 255 = blanc 


```
limite de x et y ->
		si env->aa = 1 alors
			xmax = env->raysurfaceaa->w
			ymax = env->raysurfaceaa->y 
		si env->aa = 0 alors
			xmax = env->raysurface->w
			ymax = env->raysurface->y 
```

updatepixel va prendre automatiquement la bonne surface sur laquelle draw et dire au programe de l'afficher au prochain draw
