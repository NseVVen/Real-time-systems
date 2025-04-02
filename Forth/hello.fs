VARIABLE sum    \ накопленная сумма
VARIABLE odd    \ текущее нечётное число
VARIABLE cnt    \ счётчик итераций

: sqrt-int ( n -- n )
    dup 0 < if drop -1 exit then  \ если n < 0, вернуть -1
    dup 0 = if drop 0 exit then   \ если n = 0, вернуть 0
    >r                           \ сохраняем исходное n в return stack
    0 sum !
    1 odd !
    0 cnt !
    BEGIN
       sum @ r@ <=              \ пока sum <= n (n из return stack)
    WHILE
       odd @ sum @ + sum !
       odd @ 2 + odd !
       cnt @ 1 + cnt !
    REPEAT
    cnt @ 1 -                   \ результат = cnt - 1
    rdrop ;                     \ удаляем n из return stack