# Cerberus Engine

## Short description
Cerberus Engine is a basic 3D engine developed for educational purposes. It provides essential tools for loading and displaying 3D models, along with texture support. The project aims to demonstrate fundamental concepts in 3D graphics and rendering.

### Project GitHub:  
[DHazardFenrir/3D_Engine](https://github.com/DHazardFenrir/3D_Engine)

---

## How to use the engine
1. **Controls**:
   - **W, A, S, D**: Move the camera forward, left, backward, and right.
   - **Arrow Keys**: Rotate the camera.
   - **Mouse**: Rotate the camera freely.
   - **Alt + Left Mouse Button**: Orbit around the model.
   - **F**: Focus on the selected model.
   - **Shift**: Double the camera movement speed.
   - Note: Camera rotation is limited to 90 degrees (up and down) to prevent excessive tilting.

2. **Loading Models**:
   - Open the `models` folder located inside the `GAME` directory.
   - Drag and drop any `.gltf` file to the engine to visualize the 3D model.

3. **Loading Textures**:
   - Textures should be in PNG, JPG, JPEG, PPM, BMP, DDS, or TGA formats.
   - Drag and drop any valid image file to apply textures to the 3D models.

4. **UI Interface**:
   - The engine includes an **imgui-based UI** that provides useful information such as logs, FPS, MS, and details about the loaded texture and model.

---

## Additional comments
This engine is designed primarily for educational purposes, showcasing foundational concepts of 3D graphics and rendering. The included models—**BakerHouse**, **Duck**, and **DamagedHelmet**—are used to demonstrate loading and rendering 3D assets within the engine.

Feel free to explore and experiment with the provided controls and models. For any further clarification or issues, please refer to the project's GitHub page.
