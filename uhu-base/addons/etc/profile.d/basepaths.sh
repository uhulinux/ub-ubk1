PATH="/bin:/usr/bin:/usr/local/bin"
export PATH

if [[ $UID -eq 0 ]]
then
    export PATH=${PATH}:/sbin:/usr/sbin:/usr/local/sbin
fi

# If user ID is greater than or equal to 1000 & if ~/bin exists and is a directory & if ~/bin is not already in your $PATH
# then export ~/bin to your $PATH.
if [[ $UID -ge 1000 && -d $HOME/bin && -z $(echo $PATH | grep -o $HOME/bin) ]]
then
    export PATH=$HOME/bin:${PATH}
fi
