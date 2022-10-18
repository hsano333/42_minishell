/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/18 16:48:52 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_expand.h"
#include "libft_str.h"
#include "lexer_util.h"
#include "dir.h"

int	expand_loop(char *ast_word, char *dirname, char *filename);
t_ast_end_mode	is_matched_file_suffix(char *ast_word, char *dirname, char *filename);
t_ast_end_mode	is_matched_file_prefix(char *ast_word, char *dirname, char *filename);

void	get_prefix_dir(char *str, char *filename, size_t *i)
{
	//char	tmp;
	char	*p_ast;
	char	*p_slash;
	//DIR	*dir;

	printf("str=%s\n", str);
	p_ast = ft_strchr(str, '*');
	p_ast[0] = '\0';
	p_slash = ft_strrchr(str, '/');
	printf("get prefix dir No.0, p_slash=%s\n", p_slash);
	p_ast[0] = '*';
	*i = 0;
	if (p_slash == NULL)
	{
		printf("get prefix dir No.1\n");
		ft_strlcpy(filename, "/home/sano/work/42/minishell", PATH_MAX + 1);
		char *tmp = "/home/sano/work/42/minishell";
		printf("current path?=%s\n", tmp);
		return ;
		//kreturn (tmp);
	}
	else if (str[0] == '/')
	{
		printf("get prefix dir No.2\n");
		//p_slash[0] = '\0';
		printf("p_slash=%s\n",str);
		printf("test No.1\n");

		p_slash[0] = '\0';
		printf("test No.2\n");
		ft_strlcpy(filename, str, PATH_MAX + 1);
		printf("test No.3\n");

		*i = (size_t)(p_slash - str) + 1;
		printf("test No.4\n");
		p_slash[0] = '/';
		printf("test No.5\n");
		printf("get prefix dir No.3 i=%zu\n", *i);
		return ;
	}

	printf("get prefix dir No.3\n");
	ft_strlcpy(filename, "/home/sano/work/42/minishell", PATH_MAX + 1);
	ft_strlcat(filename, "/", PATH_MAX + 1);
	p_slash[0] = '\0';
	ft_strlcat(filename, str, PATH_MAX + 1);
	*i = (size_t)(p_slash - str) + 1;
	p_slash[0] = '/';
	printf("filename=%s\n", filename);
	//dir = opendir(str);
	//p_slash[0] = '/';
	//opendir();
	//readdir();
	//return (str);
}

/*
int	is_matched_suffix(char *filename, char *word)
{

	if (ft_strnstr(word, filename, ft_strlen(word)))
	{

	}


}
*/

t_ast_end_mode	is_equal_or_asterisk(char *ast_word, char *filename)
{

	size_t	i;
	//size_t	len;

	i = 0;
	while (filename[i] && ast_word[i])
	{
		if (filename[i] != ast_word[i] && ast_word[i] == '*' )
		{
			if (ast_word[i + 1] == '/')
				return (NEXT_DIR);
			return (NEXT_ASTERISK);
		}
		else if (filename[i] != ast_word[i])
			return (FALSE_END);
		i++;
		//return (FLASE_END);
	}
	if (!filename[i] && ast_word[i] == '/')
		return (NEXT_DIR);
	if (filename[i] == ast_word[i])
		return (TRUE_END);
	return (FALSE_END);

}

t_ast_end_mode	is_matched_file_prefix(char *ast_word, char *dirname, char *filename)
{
	//size_t	cnt;
	size_t	i;
	//char	*filename;
	//char	word;
	//size_t	len;
	t_ast_end_mode	rval;
	//char	*sla_p;
	//char	*ast_word;
	//char	*ast_p;


	i = 0;
	printf("is_matched_file No.0 ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
	while (filename[i] || ast_word[i])
	{
		//if (mode == PREFIX////)
		{
			//printf("is_matched_file No.1 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
			//if (filename[i] != ast_word[i] && ast_word[i] == '/' )
			//{
				//len = ft_strlen(dirname);
				//ft_strlcat(dirname, filename, PATH_MAX + 1);
				////////////printf("is_matched_file No.2 ast_word=%s, dirname=%s, filename=%s, \n", ast_word, dirname, filename);
				//expand_loop(&(ast_word[i + 1]), dirname, filename);
				//dirname[len] = '\0';
				////printf("is_matched_file No.3 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
			//}
			if (filename[i] != ast_word[i] && ast_word[i] == '*' )
			{
				//printf("is_matched_file No.4 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
				//ast_p = ft_strchr(&(ast_word[i + 1]), '*');
				//sla_p = ft_strchr(&(ast_word[i + 1]), '/');
				//if (sla_p > ast_p && ast_p)
					//sla_p[0] = '\0';
				printf("is_matched_file No.5 , ast_word=%s, dirname=%s, filename=%s, \n", ast_word, dirname, filename);
				if (ast_word[i + 1] == '/')
				{
					ft_strlcat(dirname,filename, PATH_MAX + 1);
					printf("is_matched_file No.6, ast_word=%s, dirname=%s, filename=%s, \n", ast_word, dirname, filename);
					return (expand_loop(&(ast_word[i + 2]), dirname, filename));
				}
				else if (ast_word[i + 1] == '\0')
				{
					//printf("true No.1 dirname=%s, filename=%s\n", dirname, filename);
					return (true);
				}
				else 
				{
					printf("is_matched_file No.6-2 i=%zu,, ast_word=%s, dirname=%s, filename=%s, \n",i,ast_word, dirname, filename);
					//ft_strlcat(dirname, filename, ft_strlen(dirname) + i + 2);
					rval = is_matched_file_suffix(&(ast_word[i + 1]), dirname, &(filename[i]));
					if (rval == NEXT_DIR)
					{

						ft_strlcat(dirname, filename, PATH_MAX + 1);
						//ft_strlcat(dirname, "/", PATH_MAX + 1);
						printf("is_matched_file No.6-3 i=%zu,, ast_word=%s, dirname=%s, filename=%s, \n",i, ast_word, dirname, filename);
						return ( expand_loop((char *)(ft_strchr(ast_word, '/') + 1), dirname, filename));
					}
					else
					{
						printf("is_matched_file No.6-4 i=%zu, ast_word=%s, dirname=%s, filename=%s, \n",i,ast_word, dirname, filename);
						return (rval);
					}

					//if (rval == true)
						//printf("rval true\n");

				}
				//printf("is_matched_file No.7 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
			}
			else if (filename[i] != ast_word[i])
				return (false);
			if (!filename[i] || !ast_word[i])
				break ;
		}
		i++;
	}
	printf("is_matched_file No.10, ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
	if (filename[i] == '\0' && ast_word[i] == '\0')
	{
		printf("true No.3 dirname=%s, filename=%s\n", dirname, filename);
		return (TRUE_END);
	}
	//printf("is_matched_file No.10 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
	return (FALSE_END);
}

t_ast_end_mode	is_matched_file_suffix(char *ast_word, char *dirname, char *filename)
{
	//size_t	cnt;
	size_t	i;
	//char	*filename;
	//char	word;
	//size_t	len;
	t_ast_end_mode	rval;
	//t_ast_end_mode	rval;
	//char	*sla_p;
	//char	*ast_word;
	//char	*ast_p;


	i = 0;
	printf("is_matched_file No.0 ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
	while (filename[i] || ast_word[i])
	{
		///else if (mode == SUFFIX)
		{
			ft_strlen(filename);
			if (ast_word[0] == filename[i])
			{
				rval = is_equal_or_asterisk(ast_word, &(filename[i]));
				if (rval == TRUE_END)
					return (TRUE_END);
				else if (NEXT_ASTERISK)
					rval = is_matched_file_prefix(&(ast_word[1]), dirname, &(filename[i + 1]));
				else if (rval == NEXT_DIR)
					return (NEXT_DIR);
				//printf("is_matched_file No.6 i=%zu,word=%c, ast_word=%s, dirname=%s, filename=%s, \n",i,word,ast_word, dirname, filename);
				//rval = is_matched_file(&(ast_word[1]), dirname, &(filename[i + 1]), PREFIX);
				//if (rval != FLASE_END)
					//return (rval);
			}
			//word = (ft_strncmp(ast_word, &(filename[i]), len + 1));
			//printf("is_matched_file No.6 i=%zu,word=%c,, ast_word=%s, dirname=%s, filename=%s, \n",i,word,ast_word, dirname, filename);
			//else if (ast_word[i] == '\0' || word == 0)
			//{
				//////////printf("is_matched_file No.7, ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
				//printf("true No.2-1 dirname=%s, filename=%s\n", dirname, filename);
				//return (TRUE_END);
			//}
			//else if (word == '\0')
			//{
				//dirname = ;
				////printf("is_matched_file No.8, ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
				//return (expand_loop(&(ast_word[i + 2]), dirname, filename));
			//}
			/*
			else if (ast_word[0] == '/')
			{
				//printf("true No.2-2 dirname=%s, filename=%s\n", dirname, filename);
				return (NEXT_DIR);
				//path 
				ft_strlcat(dirname, filename, PATH_MAX + 1);
				//printf("is_matched_file No.9-1 ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
				return ( expand_loop(   (char *)(ft_strchr(ast_word, '/') + 1), dirname, filename) );
				//printf("is_matched_file No.9-2 ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
			}
			*/
				//return (is_matched_suffix(&(filename[i + 1]), &(ast_word[i + 1]), SUFFIX));
			if (!filename[i])
				break ;
		}
		i++;
	}
	printf("is_matched_file No.10 ast_word=%s, dirname=%s, filename=%s, \n",ast_word, dirname, filename);
	//printf("is_matched_file No.10 mode=%d, ast_word=%s, dirname=%s, filename=%s, \n",mode, ast_word, dirname, filename);
	return (FALSE_END);
}

int	expand_loop(char *ast_word, char *dirname, char *filename)
{
	struct dirent	*ent;
	DIR	*dir;
	size_t	len;
	//char	tmp[PATH_MAX + 1];
	//char	filename[PATH_MAX + 1];

	dir = opendir(dirname);
	printf("expand_loop No.0 ast_word=%s, dirname=%s\n", ast_word, dirname);
	if (!dir)
		return (false);
	ft_strlcat(dirname, "/", PATH_MAX + 1);
	printf("expand_loop No.1 ast_word=%s, dirname=%s\n", ast_word, dirname);
	ent = readdir(dir);
	while (ent)
	{
		ft_strlcpy(filename ,ent->d_name, PATH_MAX + 1);
		//printf("expand_loop No.2 ast_word=%s, dirname=%s, filename=%s\n", ast_word, dirname, filename);

		if (ft_strncmp(filename , ".", 2) == 0 || ft_strncmp(filename , "..", 3) == 0)
			printf(". and .. is pass\n");
		else if (is_matched_file_prefix(ast_word, dirname, filename) == TRUE_END)
		{
			printf("true file: add file dirname+filename=%s%s\n", dirname, filename);
			len = ft_strlen(dirname);
			ft_strlcat(dirname, filename, PATH_MAX + 1);
			set_finded_file(dirname);
			dirname[len] = '\0';

			//printf("expand_loop No.2:true ast_word=%s, dirname=%s, filename=%s\n", ast_word, dirname, filename);
			//add_file(dirname + filename);
			//return (true);
		}
		ent = readdir(dir);
	}


	/*
	p_ast = ft_strchr(&(token->literal[i]), '*');
	p_ast[0] = '\0';
	p_slash = ft_strchr(token->literal, '/');
	if (!p_slash)
		return (1);
	printf("i=%zu\n", i);
	ent = readdir(dir);
	printf("file=%s, type=%d\n", ent->d_name, ent->d_type);
	*/

	return (0);

}

size_t	expand_asterisk(t_token *token, token_type pre_token)
{
	size_t	i;
	//struct dirent	*ent;
	char	dir[PATH_MAX + 1];
	char	filename[PATH_MAX + 1];
	//char	*finded_file;
	//char	*tmp;

	filename[0] = '\0';
	printf("astrisk No.1\n");
	if (pre_token == SINGLE_QUOTE || !token->valid || ASTERISK != (token->type & ASTERISK))
		return (false);
	printf("astrisk No.2\n");
	get_prefix_dir(token->literal, dir, &i);
	//ft_strlcpy(dir, 4 + 1);
	printf("astrisk No.3 dir=%s \n", dir);
	//ft_strlcat(dir, "/" , PATH_MAX + 1);
	if (!dir[0])
		return (0);
	//finded_file = malloc(PATH_MAX * 4);
	printf("expand_asterisk No.1 i=%zu, token->literal=%s, dir=%s, filename=%s, ast=%s \n",i, token->literal, dir, filename, &(token->literal[i]));
	expand_loop(&(token->literal[i]), dir, filename);
	printf("expand_asterisk No.2 token->literal=%s, dir=%s, filename=%s \n", token->literal, dir, filename);

	printf("i=%zu\n", i);
	/*
	ent = readdir(dir);
	while (ent)
	{
		printf("file=%s, type=%d\n", ent->d_name, ent->d_type);
		ent = readdir(dir);
	}
	*/
	printf("astersk No.5\n");
	//pre_dir = expand_recursive(token, i);
		//search_word();
	printf("end expand file:[%s]\n", get_finded_file());
	token->literal = ft_strdup(get_finded_file());
	clear_finded_file();
	return (true);
}
