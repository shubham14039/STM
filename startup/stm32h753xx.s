.syntax unified
.cpu cortex-m7
.thumb

.global _estack
.global Reset_Handler

/* Vector Table */
.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack                       /* Top of Stack */
    .word Reset_Handler                 /* Reset Handler */
    .word NMI_Handler                   /* NMI Handler */
    .word HardFault_Handler             /* Hard Fault Handler */
    .word MemManage_Handler             /* MPU Fault Handler */
    .word BusFault_Handler              /* Bus Fault Handler */
    .word UsageFault_Handler            /* Usage Fault Handler */
    .word 0                             /* Reserved */
    .word 0                             /* Reserved */
    .word 0                             /* Reserved */
    .word 0                             /* Reserved */
    .word SVC_Handler                   /* SVCall Handler */
    .word DebugMon_Handler              /* Debug Monitor Handler */
    .word 0                             /* Reserved */
    .word PendSV_Handler                /* PendSV Handler */
    .word SysTick_Handler               /* SysTick Handler */
    /* Add peripheral interrupts here as needed */

.size g_pfnVectors, .-g_pfnVectors

/* Reset Handler */
.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    /* Copy .data section from Flash to RAM */
    ldr r0, =_sidata        /* Source address in Flash */
    ldr r1, =_sdata         /* Destination start in RAM */
    ldr r2, =_edata         /* Destination end in RAM */
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r3, [r0, r4]        /* Read word from Flash */
    str r3, [r1, r4]        /* Write word to RAM */
    adds r4, r4, #4         /* Increment offset */

LoopCopyDataInit:
    adds r4, r0, r4         /* Calculate current source address */
    cmp r4, r2              /* Compare with end address */
    bcc CopyDataInit        /* Loop if not done */

    /* Zero-initialize .bss section */
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
    b LoopFillZerobss

FillZerobss:
    str r2, [r0]            /* Write zero */
    adds r0, r0, #4         /* Increment pointer */

LoopFillZerobss:
    cmp r0, r1
    bcc FillZerobss         /* Loop if not done */

    /* Call system initialization */
    bl SystemInit
    
    /* Call C library initialization (C++ constructors, etc) */
    bl __libc_init_array
    
    /* Call main() */
    bl main
    
Infinite_Loop:
    b Infinite_Loop

.size Reset_Handler, .-Reset_Handler

/* Default Exception Handlers */
.section .text.Default_Handler, "ax", %progbits
Default_Handler:
    b Default_Handler
.size Default_Handler, .-Default_Handler

/* Weak aliases for exception handlers */
.weak NMI_Handler
.thumb_set NMI_Handler, Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler

.weak MemManage_Handler
.thumb_set MemManage_Handler, Default_Handler

.weak BusFault_Handler
.thumb_set BusFault_Handler, Default_Handler

.weak UsageFault_Handler
.thumb_set UsageFault_Handler, Default_Handler

.weak SVC_Handler
.thumb_set SVC_Handler, Default_Handler

.weak DebugMon_Handler
.thumb_set DebugMon_Handler, Default_Handler

.weak PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler

.weak SystemInit
.thumb_set SystemInit, Default_Handler

.weak __libc_init_array
.thumb_set __libc_init_array, Default_Handler
