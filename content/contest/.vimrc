set cin aw ai is ts=4 sw=4 tm=500 nu rnu noeb ru cb=unnamedplus
colo darkblue | sy on | im jk <esc>
no <C-j> <C-w>j
no <C-h> <C-w>h
no <C-k> <C-w>k
no <C-l> <C-w>l

no <leader>cmp :w <bar> !g++ -g -O2 -static -Wall -Wno-unused-result -std=gnu++17 % -o %:r <CR>
no <leader>ri :!./%:r < in<CR>
no <leader>rc :!./%:r<CR>
no <leader>rr :!xclip -o > clipin && ./%:r < clipin<CR>

ca hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
