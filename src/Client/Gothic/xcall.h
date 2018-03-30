#pragma once

// -- call macro from GD3D11 (thx, atauilien!)
// ataulien: -- call macro from GothicX (thx, Zerxes!)
#define XCALL(uAddr)       \
  __asm { mov esp, ebp }   \
  __asm { pop ebp }        \
  __asm { mov eax, uAddr } \
  __asm { jmp eax }