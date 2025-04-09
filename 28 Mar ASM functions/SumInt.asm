.486
.model flat 
.data 
.code public _SumInt 
_SumInt proc
      push ebp 
      mov ebp,esp 
      mov eax,[ebp+8]
      mov eax, dword ptr[ebp+8] 
      add eax,[ebp+12]
      pop ebp
      ret 
      _SumInt endp 
      end
