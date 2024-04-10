#ifndef TYPES_H
#define TYPES_H

enum cmd{
    //is_Idling,
    is_Asking,
    is_VotingUp,
    is_VotingDown,
    is_Exiting,
    unknown
};

enum action{
    Get,
    Remove
};

enum rsrc_type{
    LIST,
    ARR
};

#endif //TYPES_H