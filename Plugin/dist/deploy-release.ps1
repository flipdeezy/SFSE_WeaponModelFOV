New-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/build/Release/*' 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/' -Force -Recurse -ErrorAction:SilentlyContinue
New-Item 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.dll' 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -Force -Recurse -ErrorAction:SilentlyContinue
if (Test-Path 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.pdb') {
New-Item 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.pdb' 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -Force -Recurse -ErrorAction:SilentlyContinue }
if (Test-Path 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.ini') {
New-Item 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.ini' 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -Force -Recurse -ErrorAction:SilentlyContinue }
if (Test-Path 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.toml') {
New-Item 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.toml' 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -Force -Recurse -ErrorAction:SilentlyContinue }
if (Test-Path 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.json') {
New-Item 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -ItemType Directory -Force -ErrorAction:SilentlyContinue
Copy-Item 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.json' 'H:/SteamLibrary/steamapps/common/Starfield/Data/SFSE/Plugins/' -Force -Recurse -ErrorAction:SilentlyContinue }
Compress-Archive -Path 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.dll','G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.ini','G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.json','G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/*.toml' -DestinationPath 'G:/Workspace/C++/SFSE_WeaponModelFOV/Plugin/dist/WeaponModelFOVSwap.v1.0.0.zip' -Force -ErrorAction:SilentlyContinue
