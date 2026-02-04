<a id="readme-top"></a>


<h1 align="center">Thread Hijacking</h3>
  <p align="center">
    This is a simple program that hijacks the main thread of another process on Windows 11. This type of program can be used for malware development, anti-cheat bypassing, and much more. :)
  </p>
</div>

![AssaultCubeDMA][product-screenshot]

<!-- ABOUT THE PROJECT -->
## About The Project

This program took me around four days to complete; I mainly used ressources from the internet, and the <a href="https://en.wikipedia.org/wiki/Windows_API" target="_blank">Windows API</a>. The goal of this project is to demonstrate thread hijacking by executing shellcode in the main thread of another process.

![GifShowcase](https://github.com/user-attachments/assets/078cdf1c-a21a-4473-b58d-54fb252faf78)

### Built With

* [![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
* [![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)](https://fr.wikipedia.org/wiki/Microsoft_Visual_Studio)
* [![Windows 11](https://img.shields.io/badge/Windows%2011-%230079d5.svg?style=for-the-badge&logo=Windows%2011&logoColor=white)](https://en.wikipedia.org/wiki/Windows_11)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

### No Compilation Needed (Recommended)

1. Download from Releases
   ```
   Download Target.exe and Threat.exe from the Releases tab of the Repository
   ```
2. Run both programs
   ```
   Run Target.exe first then Threat.exe, threat will inject the shellcode into Target.exe
   ```
3. Enjoy !
   ```
   You should see a MessageBox appearing that is attached to the main thread (paused) of Target.exe.
   If you click OK or close the MessageBox, the Target program will automatically shut down.
   ```

### Installation & Compilation

1. Clone the repo
   ```
   https://github.com/kaveOO/ThreadHijacking.git
   ```
2. Build Target.exe (Release | x64)
   ```
   Open Target.sln make sure that Configuration is set to Release and Platform set to x64
   Click on Build -> Build Solution or Ctrl+Shift+B
   ```
3. Build Threat.exe (Release | x64)
   ```
   Open Threat.sln make sure that Configuration is set to Release and Platform set to x64
   Click on Build -> Build Solution or Ctrl+Shift+B
   ```
4. Run both programs
   ```
   Run Target.exe first then Threat.exe, threat will inject the shellcode into Target.exe
   ```
5. Enjoy !
   ```
   You should see a MessageBox appearing that is attached to the main thread (paused) of Target.exe.
   If you click OK or close the MessageBox, the Target program will automatically shut down.
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Pavel Yosifovich](https://www.youtube.com/@zodiacon/videos)
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[product-screenshot]: Images/diagram.png
