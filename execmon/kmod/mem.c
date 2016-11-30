#include <asm/pgtable_types.h>
#include "includes/mem.h"
#include "includes/general.h"
#include "udis86.h"

int MEM_make_rw(unsigned long addr) {
	int ret = SUCCESS;
	pte_t * pte;
	unsigned int level;

	pte = lookup_address(addr, &level);
	if (NULL == pte) {
		ret = ERROR;
		goto cleanup;
	}

	/* Add read & write permissions if needed */
	if (0 == (pte->pte & _PAGE_RW)) {
		pte->pte |= _PAGE_RW;
	}

cleanup:
	return ret;
}

long MEM_find_insn_off(unsigned long mem_addr,
				size_t block_size,
				int insn_type,
				size_t insn_size) {
	ud_t ud;

	ud_init(&ud);
	ud_set_input_buffer(&ud, (char * ) mem_addr, block_size);
	ud_set_mode(&ud, 64);

	/* Run over the memory region */
	while(ud_disassemble(&ud)) {

		if ((insn_type == ud.mnemonic) && 
				(insn_size == ud_insn_len(&ud)) ) {
			return ud_insn_off(&ud);		
		}

	}
	
	return ERROR;
}

int MEM_patch_relative_call(unsigned long mem_addr,
				size_t block_size,
				unsigned long new_call_addr,
				unsigned long * orig_call_addr) {
	int ret = SUCCESS;
	long call_insn_offset; 
	unsigned long call_insn_addr;
	unsigned long call_relative_val;
	unsigned long new_call_relative_val;


	/* Find the relative call instruction (E8) offset */
	call_insn_offset = MEM_find_insn_off(mem_addr,
						block_size, UD_Icall, 
						RELATIVE_CALL_SIZE);	
	if (ERROR == call_insn_offset) {
		DBG_PRINT("Error patching the relative call address");
		ret = ERROR;
		goto cleanup;
	}

	/* Calculate the call instruction address */
	call_insn_addr = (mem_addr + call_insn_offset);

	MEM_make_rw(call_insn_addr);

	call_relative_val = (*((int *) (call_insn_addr + 1)));

	/* Calculate the relative value for calling the new_sys_execve */
	new_call_relative_val = ((unsigned long) new_call_addr - call_insn_addr - RELATIVE_CALL_SIZE);

	/* Save the address of the original sys_execve */
	if (NULL != orig_call_addr) {
		*orig_call_addr = call_insn_addr + RELATIVE_CALL_SIZE + call_relative_val;
	}

	/* Patch */
	(*((int*)(call_insn_addr + 1))) = (int) new_call_relative_val;

cleanup:
	return ret;
}


