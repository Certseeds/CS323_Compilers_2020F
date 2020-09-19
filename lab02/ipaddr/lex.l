%{
    int indicator = 0;
    char *addr_type = NULL;
%}
%option noyywrap
v4_n [0-9]|[1-9][0-9]|[1][0-9]{2}|2[0-4][0-9]|25[0-5]
v4 ^(({v4_n})(\.)){3}({v4_n})$
v6_n1 [0-9a-fA-F]
v6_ns {v6_n1}{1,4}
v6 ^({v6_ns}:){7}{v6_ns}$

%%
{v4} { indicator = 4; }
{v6} { indicator = 6; }
<<EOF>> {
    switch(indicator) {
        case 4:{
            addr_type = "IPv4";
            break;
        }
        case 6:{
            addr_type = "IPv6";
            break;
        }
        default:{
            addr_type = "Neither";
        }
    }
    indicator = 0;
    return 0;
}
\n {}
. {}
%%
char *validIPAddress(char *IP){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(IP);
    yylex();
    yy_delete_buffer(buf);
    return addr_type;
}
