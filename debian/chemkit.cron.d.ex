#
# Regular cron jobs for the chemkit package
#
0 4	* * *	root	[ -x /usr/bin/chemkit_maintenance ] && /usr/bin/chemkit_maintenance
