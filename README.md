<a id="readme-top"></a>


<h1 align="center">Thread Hijacking</h3>
  <p align="center">
    This is a simple program that hijacks the main thread of another process on Windows 11. This type of program can be used for malware development, anti-cheat bypassing, and much more. :)
  </p>
</div>

![AssaultCubeDMA][product-screenshot]

<!-- ABOUT THE PROJECT -->
## About The Project

This program took me around four days to complete; I mainly used ressources from the internet, and the <a href="https://en.wikipedia.org/wiki/Windows_API" target="_blank">Windows API</a>

// ADD THE VIDEO HERE


### Built With

* [![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
* [![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)](https://fr.wikipedia.org/wiki/Microsoft_Visual_Studio)
* [![Windows 11](https://img.shields.io/badge/Windows%2011-%230079d5.svg?style=for-the-badge&logo=Windows%2011&logoColor=white)](https://en.wikipedia.org/wiki/Windows_11)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

<br>

> [!WARNING]
> This project requires a Direct Memory Access (DMA) card to operate.

<br>

### No Compilation Needed

1. Download from Releases
   ```sh
   Download CompiledCheat.zip from the Releases tab of the Repository
   ```
2. Extract the .zip
   ```sh
   Extract the CompiledCheat.zip archive
   ```
3. Enjoy !
   ```
   Start AssaultCube and run AssaultCubeDMA.exe
   ```

### Installation & Compilation

1. Clone the repo
   ```sh
   git clone https://github.com/1337Corporation/AssaultCubeDMA.git
   ```
2. Build DMALibrary (Release)
   ```sh
   Open DMALibrary.sln change the configuration to Release and build it
   ```
3. Build AssaultCubeDMA (Debug)
   ```sh
   Open AssaultCubeDMA.sln keep the Debug config and build it.
   ```
4. Add MemProcFS binaries
   ```sh
   Download MemProcFS binaries from Releases tab of the Repo
   ```
5. Navigate to x64/Debug directory
   ```sh
   cd AssaultCubeDMA\AssaultCubeDMA\x64\Debug
   ```
6. Extract all binaries
   ```sh
   Extract all binaries at the root of directory (not inside a MemProcFS directory)
   ```
7. Enjoy !
   ```sh
   Start AssaultCube and run AssaultCubeDMA.exe
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

1. **Reverse Engineering AssaultCube**
   - Used IDA Pro and other tools to analyze AssaultCube's memory structure and game logic.
   - Identified player, entity, and game state addresses.

2. **Researching DMA Techniques**
   - Studied DMA hardware and external memory access methods.
   - Selected compatible DMA cards and libraries (e.g., DMALibrary, MemProcFS).

3. **Setting Up the DMA Environment**
   - Integrated DMALibrary for low-level memory access.
   - Verified communication between DMA card and target system.

4. **Implementing Memory Reading/Writing**
   - Developed C++ classes to read/write game memory externally.
   - Ensured safe and reliable access to game data structures.

5. **Building ESP Features**
   - Coded basic ESP overlays (player positions, boxes, etc.) using ImGui for rendering.
   - Linked ESP data to real-time memory reads.

6. **Testing and Debugging**
   - Ran the cheat alongside AssaultCube, iteratively fixing bugs and improving stability.
   - Used debug builds and logging for troubleshooting.

7. **Packaging and Documentation**
   - Created build scripts and release instructions.
   - Documented setup, usage, and technical details in the README.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [DMALibrary](https://github.com/Metick/DMALibrary)
* [MemProcFS (this guy is too good...)](https://github.com/ufrisk/MemProcFS)
* [UnknownCheats](https://www.unknowncheats.me/forum/index.php)
* [IDA CheatSheet](https://malwareunicorn.org/workshops/idacheatsheet.html)
* [Brain (mine)](https://en.wikipedia.org/wiki/Brain)
* [ImGui (UI & Rendering)](https://github.com/ocornut/imgui)
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[product-screenshot]: Images/diagram.png
