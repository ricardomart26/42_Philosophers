
// void	put_to_sleep(t_info *p)
// {
// 	if (p->st == eating || p->st == scratch_balls)
// 	{
// 		if (p->id == 0)
// 		{
// 			p->forks[p->id] = 0;
// 			p->forks[p->nmr_p - 1] = 0;
// 		}
// 		else
// 		{
// 			p->forks[p->id] = 0;
// 			p->forks[p->id - 1] = 0;
// 		}
// 		p->st = sleeping;
// 		usleep(p->time_to_sleep);
// 	}
// }