# SAVIR_LAB

Educational Lab with VR Interaction
This is outsourcing collaborative work with Karim Gamal & Eslam Rabie.

## INSTRUCTIONS

kindly update the files under PATH **../Content/Blueprints/L0_SafetyLab**

## Documentation

### Adjust/Modify Performance
  - You can easily control the Texture Streaming of your project by applying multiple commands in the **Output Log** ,,, example : if we want to run/test the scene with highest resolution possible we apply this command : 
```
r.texturestreaming 0
```
  - you can read more about it in the UE4 Doc of [Texture Streaming and Pooling](https://docs.unrealengine.com/4.26/en-US/RenderingAndGraphics/Textures/Streaming/Config/)

### Modeling Tools
  - in order to edit/modify any model in the scene you have to enable **Modeling Tools Editor mode** plugin,,, you can enable any plugin by going to (Edit >> Plugins >> Search for PLUGIN_NAME >> Enable >> Restart Now)
  - (EditPivot) after restarting the project,, select any Object/Actor you'd like to modify/edit in the scene then press _Shift+6_ in order to open the modeling tool bar ,, go to Transform and edit Pivot.

### Keytrigger Events/Custom Events
  - **Left Shift** : It triggers _The Inspector Vision_ which it gives specific items different covered materials based on the tag name _highlight_
    - it's located in PATH **../Content/VFX_UIUX/Blueprints/InspectorVisionController**

  - **Left Ctrl** : It makes the whole global diliation in time.
    - it's located in PATH **../Content/ThirdPersonBP/Blueprints/ThirdPersonCharacter**
  
  - 


