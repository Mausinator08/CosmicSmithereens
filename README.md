# Introduction

An example game while building the Mausinator Games Kit.

# Getting Started

## Installation

1.	Clone this repository to your development folder.
2.	Open the solution in Visual Studio 2019 from `<your-development-directory>\ExampleGame\source\example_game.sln`.
3.	After cloning and building `spdlog`: 
   1.	Right click the `CosmicSmithereens.vcxproj` item in the Solution Explorer and select `Properties`.
   2.	Under `VC++ Directories`, be sure to add the `spdlog\include\` to the `Include Directories` list for `All Configurations`.
   3.	Under `VC++ Directories`, be sure to add `spdlog\build\$(Configuration)\` to the `Library Directories` list for `All Configurations`.
   4.	Under `Linker->Input`, be sure to add `spdlogd.lib` to the `Additional Dependencies` list for the `Debug` Configuration.
   5.	Under `Linker->Input`, be sure to add `spdlog.lib` to the `Additional Dependencies` list for the `Release` Configuration.
4.	To add the Visual Leak Detector library:
   1.	On the top menu bar, select `Tools->Nuget Package Manager->Nuget Package Manager for Solution...`.
   2.	In the dialog, at the top where the tabs are, go to the `Browse` tab and search for [visual leak detector].
   3.	In the results on the left, select `Visual Leak Detector`, then on the right, click the `Install` button and follow the prompts.
   4.	You may have to add `<ExampleGame directory>\Source\packages\VisualLeakDetector.<version>\lib\native\include` to the `Additional Include Directories` in the Project Properties.
   5.	You may have to add `<ExampleGame directory>\Source\packages\VisualLeakDetector.<version>\lib\native\address-model-<arch>\lib\` depending on the selected configuration to `Additional Library Directories` in the Project Properties.
   6.	Be sure to add `vld.lib` to `All Configurations` but make sure the 32 and 64 bit platform selections are done separately for the `Linker->Input->Additional Dependencies` section.

## Software dependencies

- A Windows version that supports DirectX 11/12.
- Visual Studio 2019 (All editions including Community Edition)
- Windows Development Kit (latest)
- VC++ Packages and Runtimes for Visual Studio 2019 (latest).
- `spdlog` (v1.x from source) from [https://github.com/gabime/spdlog.git](https://github.com/gabime/spdlog.git)
- (NuGet) `Visual Leak Detector v2.5.0.0

## Latest releases

<none>

# Build and Test

<work-in-progress>

# Contribute

TBD…