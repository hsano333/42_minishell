/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:51:15 by maoyagi           #+#    #+#             */
/*   Updated: 2022/10/10 14:51:15 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"
#include "signal_minishell.h"

void default_handler(int sig, siginfo_t *siginfo, void *unused)
{
    (void)unused;
    //(void)sig;
    (void)siginfo;

    // set_error_code

    if (sig == SIGINT)
    {
        // printf("\n");
        ft_putstr_fd("\n", STDERR_FILENO);
        //通常、改行を出力した後、新しい (空の) 行に移動したことを更新ルーチンに伝えます。
        rl_on_new_line();
        //  rl_line_bufferの内容をtextに置き換えます。可能であれば、ポイントとマークは保持されます。clear_undoがゼロ以外の場合、現在の行に関連付けられた取り消しリストがクリアされます 。
        rl_replace_line("", 0);
        // rl_line_bufferの現在の内容を反映するように、画面に表示される内容を変更します。
        rl_redisplay();
    }
}

void fork_handler(int sig, siginfo_t *siginfo, void *unused)
{
    (void)unused;
    //(void)sig;
    (void)siginfo;

    // set_error_code

    if (sig == SIGINT)
    {
        // printf("\n");
        ft_putstr_fd("\n", STDERR_FILENO);
        //通常、改行を出力した後、新しい (空の) 行に移動したことを更新ルーチンに伝えます。
        rl_on_new_line();
        //  rl_line_bufferの内容をtextに置き換えます。可能であれば、ポイントとマークは保持されます。clear_undoがゼロ以外の場合、現在の行に関連付けられた取り消しリストがクリアされます 。
        rl_replace_line("", 0);

        // pid kill
        // kill(g_pid, SIGINT);
        //printf("signal: %d\n", g_pid);
        // exit(130);
    }
    else if (sig == SIGQUIT)
    {
        // printf("\n");
        ft_putstr_fd("quit\n", STDERR_FILENO);
        //通常、改行を出力した後、新しい (空の) 行に移動したことを更新ルーチンに伝えます。
        rl_on_new_line();
        //  rl_line_bufferの内容をtextに置き換えます。可能であれば、ポイントとマークは保持されます。clear_undoがゼロ以外の場合、現在の行に関連付けられた取り消しリストがクリアされます 。
        rl_replace_line("", 0);

        //  pid kill
        //kill(g_pid, SIGINT);
        //printf("signal: %d\n", g_pid);
        // exit(130);
    }
}

void exit_handler(int sig, siginfo_t *siginfo, void *unused)
{
    (void)unused;
    //(void)sig;
    (void)siginfo;

    // set_error_code
    kill(-1, SIGINT);
    if (sig == SIGINT)
    {
        printf("exit handler\n");
        exit(130);
        printf("exit\n");
    }
}

static void handle_cmd_signal(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        ft_putstr_fd("\n", STDERR_FILENO);
        // rl_on_new_line
        //通常、改行を出力した後、新しい (空の) 行に移動したことを更新ルーチンに伝えます。
        rl_on_new_line();
        // rl_replace_line (const char *text, int clear_undo)
        //  rl_line_bufferの内容をtextに置き換えます。可能であれば、ポイントとマークは保持されます。clear_undoがゼロ以外の場合、現在の行に関連付けられた取り消しリストがクリアされます 。
        rl_replace_line("", 0);
    }
}

static void handle_global_signal(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n", STDERR_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        // kill(0, SIGHUP);
        //  rl_redisplay
        //  readlineの内容を表示
        //  rl_line_bufferの現在の内容を反映するように、画面に表示される内容を変更します。
        rl_redisplay();
    }
}

void handle_cmd_signals(void)
{
    // signal(SIGQUIT, SIG_IGN);
    signal(SIGQUIT, handle_cmd_signal);
    // signal(SIGINT, SIG_IGN);
    signal(SIGINT, handle_cmd_signal);
}

void handle_global_signals(void)
{
    signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, SIG_IGN);
    signal(SIGINT, handle_global_signal);
}

// t_sigaction act;

bool set_signal(t_signal_mode mode)
{
    t_sigaction act;

    sigemptyset(&(act.sa_mask));
    // sigaddset(&(act.sa_mask), SIGINT);
    act.sa_flags = SA_SIGINFO;

    if (mode == DEFAULT_MODE)
    {
        sigaddset(&(act.sa_mask), SIGINT);
        // act.sa_sigaction = default_handler;
        act.sa_handler = handle_global_signal;
        if (sigaction(SIGINT, &act, NULL) < 0)
            return (false);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (mode == FORK_MODE)
    {
        sigaddset(&(act.sa_mask), SIGINT);
        sigaddset(&(act.sa_mask), SIGQUIT);

        act.sa_handler = handle_cmd_signal;
        // act.sa_sigaction = fork_handler;
        //  signal(SIGQUIT, SIG_IGN);
        if (sigaction(SIGINT, &act, NULL) < 0)
            return (false);
        if (sigaction(SIGQUIT, &act, NULL) < 0)
            return (false);
    }
    else if (mode == CHILD_MODE)
    {
        sigaddset(&(act.sa_mask), SIGINT);
        sigaddset(&(act.sa_mask), SIGQUIT);

        // act.sa_sigaction = SIG_IGN;
        // signal(SIGQUIT, SIG_IGN);
        // signal(SIGINT, SIG_IGN);
        // act.sa_sigaction = exit_handler;
        // act.sa_sigaction = NULL;
        act.sa_handler = handle_cmd_signal;
        // signal(SIGQUIT, SIG_IGN);

        if (sigaction(SIGINT, &act, NULL) < 0)
            return (false);
        if (sigaction(SIGQUIT, &act, NULL) < 0)
            return (false);

        // signal(SIGINT, exit_handler);
        // signal(SIGQUIT, exit_handler);
    }

    return (true);
}

static void handle_heredoc_signal(int sig){
    extern sig_atomic_t signal_flag;

    if (sig == SIGINT){
       signal_flag = 1;
       //ft_putstr_fd("\n", STDERR_FILENO);
       rl_on_new_line();
       rl_replace_line("", 0);
       rl_redisplay();
    }
}

void handle_heredoc_signals(){
    signal(SIGINT, handle_heredoc_signal);
}
