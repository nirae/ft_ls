/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 17:56:23 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/13 18:21:17 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void	print_type(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFDIR)
		printf("Type: Repertoire\n");
	else if ((mode & S_IFMT) == S_IFREG)
		printf("Type: Fichier\n");
	else if ((mode & S_IFMT) == S_IFLNK)
		printf("Type: Lien symbolique\n");
}

void	print_mode(mode_t mode)
{
	char	model[] = "rwxrwxrwx";
	char	result[10];
	int		i = -1;

	while (++i < 9)
	{
		if (mode & (1 << (8 - i)))
			result[i] = model[i];
		else
			result[i] = '-';
	}
	result[9] = '\0';
	printf("Droits: %s\n", result);
}

void	print_owner(uid_t uid)
{
	struct passwd *tmp;

	tmp = getpwuid(uid);
	printf("Proprietaire: %s\n", tmp->pw_name);
}

void	print_group(gid_t gid)
{
	struct group *tmp;

	tmp = getgrgid(gid);
	printf("groupe: %s\n", tmp->gr_name);
}

void	print_time(time_t *timer)
{
	char *cctime = ctime(timer);
	char month[4];
	char day[3];
	char hour[3];
	char min[3];
	char year[5];
	
	int i = -1;
	while (++i < 3)
		month[i] = cctime[4 + i];
	month[i] = '\0';
	i = -1;
	while (++i < 2)
		day[i] = cctime[8 + i];
	day[i] = '\0';
	i = -1;
	while (++i < 2)
		hour[i] = cctime[11 + i];
	hour[i] = '\0';
	i = -1;
	while (++i < 2)
		min[i] = cctime[14 + i];
	min[i] = '\0';
	i = -1;
	while (++i < 4)
		year[i] = cctime[20 + i];
	year[i] = '\0';

	if (*timer < (time(NULL) - 15778800))
		printf("%s %s %5s", month, day, year);
	else
		printf("%s %s %s:%s", month, day, hour, min);
}

int		main(int argc, char **argv)
{
	int i = 0;
	struct stat file;

	if (argc > 1)
	{
		while (argv[++i])
		{
			if ((lstat(argv[i], &file)) < 0)
			{
				printf("impossible d'ouvrir le fichier %s\n", argv[i]);
				break;
			}
			printf("Nom: %s\n", argv[i]);
			print_type(file.st_mode);
			printf("Mode: %ho\n", file.st_mode);
			print_mode(file.st_mode);
			printf("Nombre de liens: %d\n", file.st_nlink);
			print_owner(file.st_uid);
			print_group(file.st_gid);
			printf("Taille: %lld octets\n", file.st_size);
			printf("date : %s\n", ctime(&file.st_mtimespec.tv_sec));
			print_time(&file.st_mtimespec.tv_sec);
			printf("\n");
		}
	}
	else
		printf("pas d'arguments\n");
	return (0);
}
/*
int		main(void)
{
	DIR				*dirp;
	struct dirent	*dir;
	struct stat		file;
	char			*name;

	name = malloc(2);
	name = "/";
	if (!(dirp = opendir("/")))
	{
		printf("Le dossier n'a pas pu etre ouvert\n");
		return (0);
	}
	while ((dir = readdir(dirp)) != NULL)
	{
		printf("nom = %s, d_type = %d\n", dir->d_name, dir->d_type);
		if ((lstat(dir->d_name, &file)) < 0)
		{
			printf("erreur = %d\n", errno);
			return (0);
		}
		printf("time = %ld\n", file.st_atimespec.tv_sec);
		if (dir->d_type == 8)
		{
			printf("FICHIER\n");
			stat(dir->d_name, &file);
			printf("time = %s\n", ctime(&file.st_mtimespec.tv_sec));
		}
	}
	closedir(dirp);
	return (0);
}*/
