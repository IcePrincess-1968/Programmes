void DOWN_TO_UP()
{
	build(1,0,sz,true);
	int i,j,pt;
	sort(col+1,col+cnum+1,cmp_SMALLTOBIG);;
	pt=sz;
	for (i=1;i<=cnum;i++)
		if (col[i].dir)
		{
			while (pt<=col[i].ed)
			{
				for (j=0;j<int(row_arrow[pt].size());j++)
				{
					st=row_arrow[pt][j].st;ed=row_arrow[pt][j].ed;ind=row_arrow[pt][j].ind;
					update(1,st,ed,true,pt);
				}
			}
			pair<int,resArrow> res=query(1,col[i].pos,true);
			//a real arrow
			if (col[i].st!=col[i].ed)
			{
				if (res<=-INF)
					v[col[i].ind].pb(mp(++tot,col[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a horizontal arrow
						v[col[i].ind].pb(mp(res.y.ind,col[i].ed-res.x+myabs(res.y.ed-col[i].pos)));
					else
						//meet a vertical arrow
						v[col[i].ind].pb(mp(res.y.ind,col[i].ed-res.x+res.y.len));
				}
				st=ed=col[i].pos;ind=col[i].ind;len=myabs(col[i].ed-col[i].st)+1;
				update(1,st,ed,true,col[i].st);
			}
			//a query arrow
			else
			{
				if (res.x<=-INF)
					//touch edge
					v[row[i].ind].pb(mp(++tot,col[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a vertical arrow
						v[col[i].ind].pb(mp(res.y.ind,col[i].ed-res.x+myabs(res.y.ed-col[i].pos)));


bool cmp_BIGTOSMALL(read_arrow x,read_arrow y)
{
	if (max(x.st,x.ed)!=max(y.st,y.ed))
		return max(x.st,x.ed)>max(y.st,y.ed);
	return myabs(x.ed-x.st+1)>myabs(y.ed-y.st+1);
}

bool cmp_SMALLTOBIG(read_arrow x,read_arrow y)
{
	if (max(x.st,x.ed)!=max(y.st,y.ed))
		return max(x.st,x.ed)<max(y.st,y.ed);
	return myabs(x.ed-x.st+1)>myabs(y.ed-y.st+1);
}

void RIGHT_TO_LEFT()
{
	build(1,0,sz,false);
	int i,j,pt;
	sort(row+1,row+rnum+1,cmp_BIGTOSMALL);
	pt=sz;
	for (i=1;i<=rnum;i++)
	{
		if (row[i].dir && row[i].st==row[i].ed) continue;
		while (pt>=max(row[i].st,row[i].ed))
		{
			for (j=0;j<int(col_arrow[pt].size());j++)
			{
				st=col_arrow[pt][j].st;ed=col_arrow[pt][j].ed;
				if (st==ed) continue;
				ind=col_arrow[pt][j].ind;len=myabs(ed-st+1);
				update(1,st,ed,false,pt);
			}
		}
		if (row[i].dir)
		{
			st=ed=row[i].pos;
			ind=row[i].ind;len=myabs(row[i].st-row[i].ed)+1;
			update(1,st,ed,false,row[i].ed);
			continue;
		}
		pair<int,resArrow> res=query(1,row[i].pos,false);
		if (row[i].st!=row[i].ed)
			//a real arrow
			if (res.x>=INF)
				v[row[i].ind].pb(mp(RIGHT_INF,sz-row[i].ed));
			else
			{
				if (res.y.st!=res.y.ed)
					//meet a vertical arrow
					v[row[i].ind].pb(mp(res.y.ind,res.x-row[i].ed+myabs(res.y.ed-row[i].pos)));
				else
					//meet a horizontal arrow
					
