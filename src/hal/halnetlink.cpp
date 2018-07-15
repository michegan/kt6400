#ifdef _WIN32
    #include "halnetlink_win32.cpp"
#else
    #include "halnetlink_x11.cpp"
#endif