# RTRT_CPU
**rtrt_cpu** is a real-rime ray tracer implementation on the CPU (the name is fairly self explanatory). It's multithreaded and dynamically uses different target resolutions to maintain a playable framerate.

This is my implementation of the instructions from the awesome book ["Ray Tracing in One Weekend"](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Libraries used
- **[Thirteen](https://github.com/Atrix256/Thirteen)**: An awesome minimal & cross-platform graphics interface used for window management & pixel rendering
- that's it :]

## Compiling
**Linux**: 
- Dependencies: GNU Make, G++
- Run `make` in the root of the project, the output will be placed at `bin/build`
  - (You can also just run `make run` to automatically build & run)

**Windows:**
You're on your own for now, sorry :( I'll add windows build support soon

## License
**rtrt_cpu** is licensed under the **MIT License**. Please see [LICENSE](LICENSE) for more details.
