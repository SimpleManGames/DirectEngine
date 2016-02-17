#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

// Define
#define SafeRelease(x) { if(x) { x->Release(); x = nullptr;} } // Macro for releasing COM object
#define SafeDelete(x) { if(x) { delete x; x = nullptr; } }

#endif // !_DELETEMACRO_H

