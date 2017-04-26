#include"inclusions.h"
#include"inputhandler.h"

int main(int argc, char** argv)
{
        boost::filesystem::path pwd(argv[0]);
        pwd = boost::filesystem::canonical(pwd.parent_path());
        InputHandler iph(pwd);
        iph.Loop();
        return 0;
}
