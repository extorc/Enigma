## Enigma
Enigma is a renderer working on the Ray Tracing technique written by a Computer Science freshman utilising C++.
## Installation
* To Install <br>
Clone the repo using <br>
```bash
  git clone --recursive https://github.com/extorc/Enigma
```
* Set the project up <br>
```bash
  cd build
  cmake ../
```
Make sure cmake on your machine is configured to run the appropriate version of CXX compiler by running the `cmake -G` command.
* Compile and execute
```bash
  make
  Enigma
```
## Working of the project
The Project uses <a href = "https://www.opengl.org/">OpenGL</a> to display framebuffers and to carry out matrix and vector calculations.<br>
* <a href = "https://github.com/glfw/glfw">Glfw</a> for instantiating a window.
* <a href = "https://github.com/Dav1dde/glad">Glad</a> for an OpenGL wrapper.
* <a href = "https://github.com/g-truc/glm">Glm</a> for matrix and vector mathematics.
## Documentation
The application is entered from the `main.cpp` where the window is created using a wrapper `Window` struct. The GLFW and GLAD libraries are initialized in the `createWindow` function implemented in `Graphics.h`.<br>
A Scene object is created to which Sphere, Plane and Material objects are pushed.<br><br>
A `glm::vec4` pixel vector is created to store the final framebuffer which is initialized to all zeroes. Another vector of the same dimension is created called `accumilation` to store the pre-normalized pixel data. The pixel data will be first calculated and appended to accumilation every sample and then normalized and finalized into pixel vector.<br><br>
A `Camera` class is defined where we first generate all the rays, starting from the camera origin, pointing to the individual pixels situated `FOV` distance away.<br><br>
Inside the Render loop, processing is carried out per sample per pixel. So the processing is carried out a total of samples * pixels number of times. For each pixel sample, the corresponding generated `Ray` is accessed, the color for the poxel is calculated using a renderer function called `processPixel()` and appended to the accumilation vector. This is then normalized as mmentioned earlier.
```c++
if(sampleCount < maxSampleCount){
  for(int j = 0; j < image_height; j++){
    for(int i = 0; i < image_width; i++){                                             //For every pixel on the screen
      Ray ray = {
        glm::normalize(camera.rayDirections[j * image_width + i]),
        camera.cameraPosition
      };                                                                              //Generate a ray
      auto color = renderer.processPixel(ray);                                        //And process the ray
      accumulation[j * camera.u + i] += color;                                        //Accumulate the data processed
      pixels[j * camera.u + i] = accumulation[j * camera.u + i]/(float)sampleCount;   //And update pixel data based on accumulation and sample count
    }
  }
  sampleCount++;                                                                      //Update sample count
}
```
