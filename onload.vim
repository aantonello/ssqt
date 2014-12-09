"" Vim Project plugin configuration script.

"" Do this only once
if exists('g:did_ssqt_config')
    finish
endif
let g:did_ssqt_config = 1

"" Enable Qt types and classes highlight.
let g:cpp_qt = 1

"" ApplyTemplate plugin configuration
let g:atpl_UsersList['@AUTHORMAIL@'] = '<aantonello@paralaxe.com.br>'
let g:atpl_UsersList['@PROJECT@']    = 'Super Simple for Qt 5'
let g:atpl_UsersList['@VERSION@']    = '1.2'
let g:atpl_UsersList['@OWNER@']      = 'Paralaxe Tecnologia Ltda.'

"" ctags files
set tags=tags
set tags+=$WORKHOME/libs/qt-5.3/core.tags
set tags+=$WORKHOME/libs/qt-5.3/gui.tags
set tags+=$WORKHOME/libs/qt-5.3/widgets.tags

"" OmniCppComplete configuration
let OmniCpp_MayCompleteDot = 0
let OmniCpp_MayCompleteArrow = 0
let OmniCpp_ShowPrototypeInAbbr = 1
let OmniCpp_DefaultNamespace = ['Qt']

call omni#cpp#complete#Init()

"" I'm working on Windows 7 and it doesn't natively supports UTF-8 encoding.
"" So, some work must be done when a new file is created.
augroup SSQT
    au!
    au BufNewFile *.cpp,*.hpp,*.h   set fenc=utf8 nobomb
augroup END

