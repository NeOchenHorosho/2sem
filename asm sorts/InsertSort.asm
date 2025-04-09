.486
.model flat 
.data 
.code public _InsertSort
_InsertSort proc
		push ebp
		mov ebp, esp
		mov ecx, [ebp + 12]
		sub ecx, 1
		mov ebx, [ebp + 8]
	for1:
		mov esi, ecx
		sub esi, 1
		mov eax, [ebx + esi * 4]
		add esi, 1
	while_cycle:
		cmp esi, [ebp + 12]
		jge func_end
		mov edx, [ebx + esi * 4]
		cmp eax, edx
		jle func_end
		sub esi, 1
		mov[ebx + esi * 4], edx
		add esi, 2
		jmp while_cycle
	func_end :
		sub esi, 1
		mov[ebx + esi * 4], eax
		loop for1
		pop ebp
		ret
_InsertSort endp
end
