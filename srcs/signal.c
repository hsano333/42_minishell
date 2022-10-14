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

void sigint_handler(int sig, siginfo_t *siginfo, void *unused)
{
    (void)unused;
    //(void)sig;
    (void)siginfo;

    // set_error_code

    if (sig == SIGINT)
    {
        printf("\n");
        //通常、改行を出力した後、新しい (空の) 行に移動したことを更新ルーチンに伝えます。
        rl_on_new_line();
        //  rl_line_bufferの内容をtextに置き換えます。可能であれば、ポイントとマークは保持されます。clear_undoがゼロ以外の場合、現在の行に関連付けられた取り消しリストがクリアされます 。
        rl_replace_line("", 0);
        // rl_line_bufferの現在の内容を反映するように、画面に表示される内容を変更します。
        rl_redisplay();
    }
}

bool set_sighandler(t_sigaction *act, void (*handler)(int, siginfo_t *, void *))
{
    (*act).sa_sigaction = handler;
    if (sigaction(SIGINT, act, NULL) < 0)
        return (false);
    return (true);
}

bool init_signal(t_sigaction *act)
{
    sigemptyset(&(act)->sa_mask);
    sigaddset(&(act)->sa_mask, SIGINT);
    // sigaddset(&(act)->sa_mask, SIGQUIT);

    (*act).sa_flags = SA_SIGINFO;
    if (!set_sighandler(act, &sigint_handler))
        return (false);

    /*
    (*act).sa_sigaction = sig_handler;
    if (sigaction(SIGINT, act, NULL) < 0)
        return (false);
    */
    signal(SIGQUIT, SIG_IGN);

    // CTRL + D ->exit

    /*
    sigaddset(&(act)->sa_mask, SIGQUIT);

    if (sigaction(SIGQUIT, act, NULL))
        return (false);
    */

    // CTRL + \ -> do not nothing
    return (true);
}