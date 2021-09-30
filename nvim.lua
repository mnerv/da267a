-- Command shortcuts
local opt = vim.opt
local api = vim.api
local fn  = vim.fn
local cmd = vim.cmd

-- Configure plugins
require('packer').startup(function()
  -- Packer can manage itself
  use 'wbthomason/packer.nvim'
  use {
    'nvim-telescope/telescope.nvim',
    requires = { {'nvim-lua/plenary.nvim'} },
    config   = function()
      local actions = require 'telescope.actions'
      local api     = vim.api

      local function set_map(map, cmd_name)
        return api.nvim_set_keymap('n', map, "<cmd>lua require('telescope.builtin')."..cmd_name.."()<cr>", {
          noremap = true,
          silent  = true
        })
      end

      local function set_map_raw(map, cmd)
        return api.nvim_set_keymap('n', map, cmd, {
          noremap = true,
          silent  = true
        })
      end

      set_map('ff', 'find_files')
      set_map('fg', 'live_grep')
      set_map('fb', 'buffers')
      set_map('fh', 'help_tags')

      set_map_raw('fd', '<cmd>Telescope find_files find_command=rg,--ignore,--hidden,--files<cr>')
      set_map_raw('<C-P>', '<cmd>Telescope commands<cr>')
      set_map_raw('tt', '<cmd>Telescope<cr>')

      require 'telescope'.setup {
        defaults = {
          initial_mode = 'insert',
          file_ignore_patterns = { '.git' },
          mappings = {
            i = {
              ["<esc>"] = actions.close,
              ["<C-j>"] = actions.move_selection_next,
              ["<C-k>"] = actions.move_selection_previous,
            },
          },
          color_devicons = true,
        },
        pickers = {
          buffers = {
            mappings = {
              n = {
                ["<c-d>"] = require'telescope.actions'.delete_buffer,
              }
            }
          }
        },
      }
    end
  }
  use {
    'nvim-treesitter/nvim-treesitter',
    config = function()
      require 'nvim-treesitter.configs'.setup {
       ensure_installed = 'maintained',
        highlight       = {enable = true}
      }
    end,
  }
  -- Language Server Protocol
  use {
    'neovim/nvim-lspconfig',
    config = function()
      local on_attach = function(client, bufnr)
        local function buf_set_keymap(...) vim.api.nvim_buf_set_keymap(bufnr, ...) end
        local function buf_set_option(...) vim.api.nvim_buf_set_option(bufnr, ...) end

        -- Enable completion triggered by <c-x><c-o>
        buf_set_option('omnifunc', 'v:lua.vim.lsp.omnifunc')

        -- Mappings.
        local opts = { noremap=true, silent=true }

        -- See `:help vim.lsp.*` for documentation on any of the below functions
        buf_set_keymap('n', 'gD',        '<cmd>lua vim.lsp.buf.declaration()<CR>', opts)
        buf_set_keymap('n', 'gd',        '<cmd>lua vim.lsp.buf.definition()<CR>', opts)
        buf_set_keymap('n', 'K',         '<cmd>lua vim.lsp.buf.hover()<CR>', opts)
        buf_set_keymap('n', 'gi',        '<cmd>lua vim.lsp.buf.implementation()<CR>', opts)
        buf_set_keymap('n', '<C-k>',     '<cmd>lua vim.lsp.buf.signature_help()<CR>', opts)
        buf_set_keymap('n', '<space>wa', '<cmd>lua vim.lsp.buf.add_workspace_folder()<CR>', opts)
        buf_set_keymap('n', '<space>wr', '<cmd>lua vim.lsp.buf.remove_workspace_folder()<CR>', opts)
        buf_set_keymap('n', '<space>wl', '<cmd>lua print(vim.inspect(vim.lsp.buf.list_workspace_folders()))<CR>', opts)
        buf_set_keymap('n', '<space>D',  '<cmd>lua vim.lsp.buf.type_definition()<CR>', opts)
        buf_set_keymap('n', '<space>rn', '<cmd>lua vim.lsp.buf.rename()<CR>', opts)
        buf_set_keymap('n', '<space>ca', '<cmd>lua vim.lsp.buf.code_action()<CR>', opts)
        buf_set_keymap('n', 'gr',        '<cmd>lua vim.lsp.buf.references()<CR>', opts)
        buf_set_keymap('n', '<space>e',  '<cmd>lua vim.lsp.diagnostic.show_line_diagnostics()<CR>', opts)
        buf_set_keymap('n', '[d',        '<cmd>lua vim.lsp.diagnostic.goto_prev()<CR>', opts)
        buf_set_keymap('n', ']d',        '<cmd>lua vim.lsp.diagnostic.goto_next()<CR>', opts)
        buf_set_keymap('n', '<space>q',  '<cmd>lua vim.lsp.diagnostic.set_loclist()<CR>', opts)
        buf_set_keymap('n', '<space>f',  '<cmd>lua vim.lsp.buf.formatting()<CR>', opts)
      end
      require'lspconfig'.ccls.setup{  -- https://github.com/MaskRay/ccls/wiki
        on_attach = on_attach,
        init_options = {
            cache = {
            directory = ".ccls-cache"
            }
        }
      }
  end,
  }

  use {
    'hoob3rt/lualine.nvim',
    requires = {'kyazdani42/nvim-web-devicons', opt = true},
    config   = function()
      require 'lualine'.setup{
        options = {
          theme = 'ayu_mirage'
        }
      }
    end
  }
  -- File tree
  use {
    'kyazdani42/nvim-tree.lua',
    requires = 'kyazdani42/nvim-web-devicons',
    config   = function()
      require'nvim-tree'.setup{}
      vim.api.nvim_set_keymap('n', '<space>tre', '<cmd>NvimTreeToggle<cr>', { noremap = true, silent = true })
    end
  }
  use {
    'lewis6991/gitsigns.nvim',
    requires = { 'nvim-lua/plenary.nvim' },
    config   = function()
      require'gitsigns'.setup{
        current_line_blame = true
      }
    end
  }

  -- Completion list
  use {
    'nvim-lua/completion-nvim',
    config = function()
      -- Completion setup
      vim.cmd "autocmd BufEnter * lua require'completion'.on_attach()"
    end,
  }
  use 'steelsojka/completion-buffers'

  -- Fix for tabing for next in list
  local function replace_code(str)
    return api.nvim_replace_termcodes(str, true, true, true)
  end
  function _G.smart_tab()
    return fn.pumvisible() == 1 and replace_code'<C-n>' or replace_code'<Tab>'
  end
  api.nvim_set_keymap('i', '<Tab>', 'v:lua.smart_tab()', {expr = true, noremap = true})
end)

--  User configs

-- Mouse support
opt.mouse = 'a'

-- Whitespaces
opt.listchars = 'tab:› ,trail:~,extends:>,precedes:<,space:∙'
opt.list      =  true   -- Show whitespace

-- Line numbers
opt.nu  = true  -- Turn on line number
opt.rnu = true  -- Set as relative mode

-- Tab and spaces
opt.expandtab = true
opt.smarttab  = true

opt.shiftwidth = 4
opt.tabstop    = 4
opt.lbr        = true  -- linebreak
opt.tw         = 500   -- text width
opt.ai         = true  -- Auto indent
opt.si         = true  -- Smart indent

-- Misc
opt.completeopt = {'menuone', 'noinsert', 'noselect'}
opt.wildmode    = {'list', 'longest'} -- Command-line completion mode
opt.splitbelow  = true                -- Put new windows below current
opt.splitright  = true                -- Put new windows right of current

-- Line wrap
opt.wrap   = false

-- Enable Background buffers
opt.hidden = true

-- Global options
vim.o.wildmenu = true    -- Command line completion mode
vim.o.wildmode = 'full'  -- Command line completion mode

-- MAP ESCAPE TO jk
api.nvim_set_keymap('i', 'jk', '<Esc>', { noremap = true })

-- Turn off line numbers in terminal mode
api.nvim_command('autocmd TermOpen * setlocal nonu nornu nolist')
api.nvim_command('autocmd TermEnter * setlocal nonu nornu nolist')
-- Escape from insert mode in terminal
api.nvim_set_keymap('t', '<Esc>', '<C-\\><C-n>', { noremap = true })

