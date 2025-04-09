.486
.model flat 
.data
.code public _SelectSort
_SelectSort proc
		push ebp
		mov ebp,esp
		mov ebx, [ebp + 8]
		mov ecx, [ebp + 12]
		sub ecx, 1
for1:
		push ecx
		mov esi, ecx
		mov edi, ecx
		sub edi, 1
for2:
		mov eax, [ebx + edi * 4]
		cmp eax, [ebx + esi * 4]
		jle endif1 
		mov esi, edi
endif1:
		sub edi, 1
		loop for2
		pop ecx
		mov eax, [ebx + esi * 4]
		mov edx, [ebx + ecx * 4]
		mov[ebx + esi * 4], edx
		mov[ebx + ecx * 4], eax
		loop for1
	pop ebp
	ret 
	_SelectSort endp 
	end
