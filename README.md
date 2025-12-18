# SimulacionFisicaVideojuegos

Como compilar y ejecutar:

Se requiere CMake y el compilador de Visual Studio, soporte C++17
En la raíz del repositorio ejecutar estos dos comandos, importante desde la CMD de Windows o PowerShell, si se usa GitBash habrá problemas ya que este proyecto está hecho para compilar con Visual Studio.

`cmake -S . -B ./out/build`

`cmake --build ./out/build --config Debug`

El exe se generará con el nombre "game_DEBUG.exe" en la carpeta /bin

---

## Manual de usuario:
- 0-3: Cambios de escenas, números estándar, no numpad (la escena de juego es la escena de la tecla 3)
- WASD: Movimiento del usuario (por defecto de la plantilla)
- Ratón y click izquierdo: Cámara (por defecto de la plantilla)
- Q: Alternar generación de partículas entre simuladas y rigidbodies
- V: Disparar
- R: reiniciar escena

En la consola se va dando información de los turnos y quien gana la partida.

---

Repositorio de las prácticas de la asignatura de Simulación Física de Videojuegos

En la carpeta skeleton estará vuestro código fuente

Necesitaréis además descomprimir el archivo que se indica a continuación en la raíz del repositorio:

Carpetas bin y common https://ucomplutense-my.sharepoint.com/:f:/g/personal/liagar05_ucm_es/ElNxHPmZVj9Ni9-8FKTKp7cBJHAarnL3vvEvG50z0QMrzg