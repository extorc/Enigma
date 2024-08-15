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
### Entry and structure
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
      pixels[j * camera.u + i] = accumulation[j * camera.u + i]/(float)sampleCount;   //Normalize pixel data based on sample count
    }
  }
  sampleCount++;                                                                      //Update sample count
}
```
### Pixel Processing
The `processPixel()` function is run for each sample of every function. The function traces the Ray generated in the camera class through its origin towards its direction using the `trace()` function which returns a `HitData` object.<br><br> Using this HitData, it is verified whether the ray intersects any scene objects, and if it does, the function generates the appropriate color for the pixel by calculating material and lighting parameters.
#### Lighting and Materials
The Lighting and Materials in this Renderer is handled in a two-step process.
* First the normal vector at a point of the object is compared with the light direction and a Albedo appropriate diffuse color is generated.
```c++
Mat objectMat = scene->materialList[scene->objects[data.objectIndex]->matIndex];
  float d = glm::max(glm::dot(data.normal, -scene->light), 0.0f);
  glm::vec3 diffuseLighted = d * objectMat.Albedo;
```
* Then the specular fall-off of the material is calculated along with the roughness of the object material by comparing the reflected version of the incident ray with the light direction.
```c++
float s = std::pow(
  glm::max(
    glm::min(
      glm::dot(
        glm::reflect(ray.rayDirection, data.normal), -scene->light)
      , 1.0f),
     0.0f),
  ROUGH_FUNC(objectMat.roughness));
glm::vec3 specularLighted = glm::vec3(1);
```
* These two stages are then combined into the `finalColor`. These `finalColor` calculations are done several times per pixel as the ray has to be bonuced off the surface of an object and intersect another object.<br> In order to implement this, the incident ray is reflected about the surface normal and ran through the trace function again in a for loop and the final color data is accumilated and returned to the main Render loop.
```c++
ray.origin = data.position + data.normal * 0.001f;
ray.rayDirection = glm::reflect(
  ray.rayDirection,
  data.normal + objectMat.roughness * glm::vec3(RAND(1.0f)-0.5f, RAND(1.0f)-0.5f, RAND(1.0f)-0.5f)
);
```
