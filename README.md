# Programming of Embedded Systems - DA267A

## Requirements

  - [PlatformIO](https://platformio.org)
  - [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/index.html) optional

## Neovim

Use neovim with intellisense. Note this guide is only written for unix like
systems, like macOS and flavors of Linux.

### Requires

  - [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/index.html)
  - [neovim 0.5.0+](https://neovim.io)
  - [packer.nvim](https://github.com/wbthomason/packer.nvim) or similiar
  - [ccls](https://github.com/MaskRay/ccls)

### Config File

`init.lua` can be found at `~/.config/nvim/init.lua` on unix like systems.
A sample `init.lua` file can found in [nvim.lua](./nvim.lua).

`neovim/nvim-lspconfig` with `ccls` lsp engine

Generate `.ccls` with this commmand

```
pio init --ide vim
```

## Visual Studio Code

On vscode you can install C/C++ Extension from Microsoft and PlatformIO extension.

