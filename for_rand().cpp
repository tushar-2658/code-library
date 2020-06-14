mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

// paste at the top and call rnd() when need to use rand()
