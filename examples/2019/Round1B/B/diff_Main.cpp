2c2
< // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
---
> #define IA_MODE        //remove comment on this line, to activate interactive problem mode
5,6c5,6
< #define COMM_TYPE ll
< #define IA_ERROR_CODE "ERROR"
---
> #define COMM_TYPE str
> #define IA_ERROR_CODE "-1"
666a667,668
> ll W;
> 
667a670
>     W = stoll(in());
669a673,674
> ll large, small;
> 
670a676,680
>     out("210");
>     large = stoll(in());
>     llog("large value saved:", large);
>     out("42");
>     small = stoll(in());
674a685,707
>     lassert(large % (1L<<35) == 0, "large not divisible by expected");
>     large /= (1L<<35);
>     ll R6 = large % (1L<<7);
>     large /= (1L<<7);
>     ll R5 = large % (1L<<7);
>     large /= (1L<<10);
>     ll R4 = large;
>     lassert(small % (1L<<7) == 0, "small not divisible by expected");
>     small /= (1L<<7);
>     small -= R6;
>     small -= 2 * R5;
>     small -= 8 * R4;
>     lassert(small % (1L<<7) == 0, "small not divisible by expected");
>     small /= (1L<<7);
>     ll R3 = small % (1L<<7);
>     small /= (1L<<7);
>     ll R2 = small % (1L<<7);
>     small /= (1L<<21);
>     ll R1 = small;
>     sstr ss;
>     ss << R1 << " " << R2 << " " << R3 << " " << R4 << " " << R5 << " " << R6;
>     out(ss.str());
>     in();
