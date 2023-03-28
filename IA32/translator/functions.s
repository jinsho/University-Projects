section .data
        incs_msg db "Quantidade de bytes lidos: "
        outcs_msg db "Quantidade de bytes escritos: "
        incs_msg_size equ 27
        outcs_msg_size equ 30
section .bss
        aux_buffer resb 11
section .text
exit:
        mov eax,1
        sub ebx,ebx
        int 0x80
_newline:
        sub eax,eax
        mov al,0xa
        mov dword[ebp-4],eax
        mov ecx,ebp
        sub ecx,4
        mov eax,4
        mov ebx,1
        mov edx,4
        int 0x80
        ret
_inmsg:
        mov eax,4
        mov ebx,1
        mov ecx,incs_msg
        mov edx,incs_msg_size
        int 0x80
        ret
_outmsg:
        mov eax,4
        mov ebx,1
        mov ecx,outcs_msg
        mov edx,outcs_msg_size
        int 0x80
        ret
input:
        enter 8,0 
        mov eax,3
        mov ebx,0
        mov ecx,aux_buffer
        mov edx,12
        int 0x80
        push eax    
        push eax
        push ecx
        call chartoint 
        mov ebx,[ebp+8]
        mov dword[ebx],eax     
        pop eax
        mov dword[ebp-8],eax
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx     
        call _inmsg    
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax
        mov eax,4
        mov ebx,1
        int 0x80    
        call _newline
        mov eax,[ebp-8]
        leave
        ret 4
output:
        enter 4,0
        mov eax,[ebp+8]
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        mov edx,ecx
        mov ecx,eax
        mov eax,4
        mov ebx,1
        int 0x80
        push eax   
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx         
        call _newline
        call _outmsg           
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax 
        mov eax,4
        mov ebx,1
        int 0x80            
        call _newline
        pop eax
        leave
        ret 4
input_c:
        enter 4,0     
        mov eax,3
        mov ebx,0
        mov ecx,[ebp+8] 
        mov edx,2
        int 0x80
        push eax    
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx    
        call _inmsg       
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax 
        mov eax,4
        mov ebx,1
        int 0x80    
        call _newline   
        pop eax 
        leave
        ret 4
output_c:
        enter 4,0    
        mov eax,4
        mov ebx,1 
        mov ecx,[ebp+8]
        mov edx,1
        int 0x80
        push eax        
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx     
        call _newline
        call _outmsg      
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax 
        mov eax,4
        mov ebx,1
        int 0x80    
        call _newline
        pop eax
        leave
        ret 4
input_s:
        enter 4,0    
        mov eax,3
        mov ebx,0
        mov ecx,[ebp+12]
        mov edx,[ebp+8]
        int 0x80
        push eax    
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx     
        call _inmsg    
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax 
        mov eax,4
        mov ebx,1
        int 0x80
        call _newline
        pop eax
        leave
        ret 8    
output_s:
        enter 4,0    
        mov eax,4
        mov ebx,1
        mov ecx,[ebp+12]
        mov edx,[ebp+8]
        int 0x80
        push eax        
        push eax
        mov eax,aux_buffer
        push eax
        call inttochar
        push eax 
        push ecx     
        call _newline        
        call _outmsg    
        pop eax
        mov edx,eax 
        pop eax
        mov ecx,eax 
        mov eax,4
        mov ebx,1
        int 0x80
        call _newline
        pop eax    
        leave
        ret 8
chartoint:
        enter 8,0
        mov esi,[ebp+12] 
        sub esi,2 
        mov [ebp-4],esi ;
        mov esi,1
        mov [ebp-8],esi     
        mov esi,[ebp+8] 
        add esi,[ebp-4] 
        sub ecx,ecx 
for1:
        mov bl,[esi]
        sub bl,0x30 
        movzx eax,bl    
        mov ebx,[ebp-8] 
        mul ebx 
        add ecx,eax     
        mov eax,10
        mov ebx,[ebp-8]
        mul ebx
        mov [ebp-8],eax 
        sub esi,1 
        mov eax,[ebp+8]
        cmp eax,esi
        jg end1
        mov eax,'-'
        mov bl,[esi]
        movzx edx,bl
        cmp eax,edx
        je end11
        jmp for1
end1:
        mov eax,ecx
        leave
        ret 8
end11:
        mov eax,-1
        imul ecx
        leave
        ret 8        
inttochar:
        enter 12,0
        mov dword[ebp-4],0
        mov dword[ebp-8],10
        mov eax,[ebp+12]
        sub ebx,ebx
        sub ecx,ecx
        cmp eax,ebx
        jge for2
        inc ecx
        sub eax,eax
        mov al,'-'
        mov esi,[ebp+8]
        mov byte[esi],al
        inc dword[ebp-4]
        mov eax,[ebp+12]
        mov ebx,-1
        imul ebx
        mov [ebp+12],eax
for2:
        mov eax,[ebp+12]
        cdq
        div dword[ebp-8]
        mov [ebp-12],eax
        add dl,0x30
        mov [ebp+12],eax
        movzx eax,dl
        push eax
        inc dword[ebp-4]
        mov eax,[ebp-12]
        sub ebx,ebx
        cmp eax,ebx
        je end2
        jmp for2
end2:    
        mov esi,[ebp+8] 
        dec dword[ebp-4] 
for22:
        mov eax,[ebp-4]
        cmp ecx,eax
        jg end22
        pop eax
        mov bl,al
        mov byte[esi+ecx],bl
        inc ecx
        jmp for22    
end22:
        mov eax,[ebp+8]
        leave
        ret 8
