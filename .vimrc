syntax on
set number
set tabstop=4 shiftwidth=4
set statusline+=%F
set ruler
set wildmenu
set showmatch
set autoindent
set cindent
set title
set nobackup
set noswapfile
set showcmd
set foldcolumn=3
inoremap jj <Esc>
nnoremap <space> :
vnoremap <space> :
nnoremap // :s@^@//@<cr>
nnoremap ?? :s@^//@@<cr>
vnoremap // :s@^@//@<cr>
vnoremap ?? :s@^//@@<cr>
" nnoremap /h :s@^@# @<cr>
" nnoremap /H :s@^# @@<cr>
" vnoremap /h :s@^@# @<cr>
" vnoremap /H :s@^# @@<cr>
nnoremap <leader>te :tabedit 
nnoremap <leader>tn :tabnew 
nnoremap <silent> <leader>h :set hlsearch!<cr>
" set backspace=indent,eol,start
" set whichwrap+=<,>,[,]
packadd! termdebug
nnoremap <F10> :Termdebug minishell<cr><cr>
" =====used in future releases=====
" let g:termdebug_config['wide'] = 1
" let g:termdebug_config['variables_window'] = 1
" let g:termdebug_config['variables_window_height'] = 10
" =====used in future releases=====
let g:termdebug_wide = 1
" let g:termdebug_variables_window = 10
set mouse=a
" set switchbuf=useopen
nnoremap <c-E> :Le<cr>
let g:netrw_winsize   = 30
" nnoremap <c-h> <c-w>h
" nnoremap <c-j> <c-w>j
" nnoremap <c-k> <c-w>k
" nnoremap <c-l> <c-w>l
nnoremap <c-left> :wincmd h<cr>
" nnoremap <c-down> :wincmd j<cr>
" nnoremap <c-up> :wincmd k<cr>
nnoremap <c-right> :wincmd l<cr>
nnoremap <F6> :call TermDebugSendCommand('continue')<cr>
nnoremap <F7> :call TermDebugSendCommand('step')<cr>
nnoremap <F8> :call TermDebugSendCommand('next')<cr>
" autocmd Filetype termdebug nnoremap <buffer> <PageUp> :call feedkeys("\<c-w><PageUp>")<cr>

" =============Python=============
nnoremap <F12> :w<cr>:!python3 %<cr>
