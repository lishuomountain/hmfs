#ifdef CONFIG_HMFS_FAST_READ
#ifndef HMFS_UTIL_H
#define HMFS_UTIL_H

#include <linux/mm.h>

static int (*__hmfs_pte_alloc_kernel) (pmd_t *pmd, unsigned long address);

static struct mm_struct *hmfs_init_mm;

/* mm/vmalloc.c */
static struct vm_struct * (*hmfs_remove_vm_area) (const void *addr);

/* mm/vmalloc.c */
static struct vm_struct * (*hmfs_find_vm_area) (const void *addr);

/* mm/vmalloc.c */
static struct vm_struct * (*hmfs_get_vm_area) (unsigned long size, 
				unsigned long flags);

static pte_t * (*hmfs_get_locked_pte) (struct mm_struct *, unsigned long, 
				spinlock_t **);

#define hmfs_pte_alloc_kernel(pmd, address)	\
	((unlikely(pmd_none(*(pmd))) && __hmfs_pte_alloc_kernel(pmd, address))? \
		NULL: pte_offset_kernel(pmd, address))

static int (*__hmfs_pud_alloc) (struct mm_struct *mm, pgd_t *pgd,
				unsigned long address);

static int (*__hmfs_pmd_alloc) (struct mm_struct *mm, pud_t *pud,
				unsigned long address);

static inline pud_t *hmfs_pud_alloc(struct mm_struct *mm, pgd_t *pgd,
				unsigned long address)
{
	return (unlikely(pgd_none(*pgd)) && __hmfs_pud_alloc(mm, pgd, address))?
					NULL: pud_offset(pgd, address);
}

static inline pmd_t *hmfs_pmd_alloc(struct mm_struct *mm, pud_t *pud, 
				unsigned long address)
{
	return (unlikely(pud_none(*pud)) && __hmfs_pmd_alloc(mm, pud, address))?
					NULL: pmd_offset(pud, address);
}

#endif

#endif
