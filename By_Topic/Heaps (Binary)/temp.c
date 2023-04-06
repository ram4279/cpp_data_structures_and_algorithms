static const struct ieee80211_opsrt73usb_mac80211_ops = {
    .tx = rt2x00mac_tx,
    .start = rt2x00mac_start,
    .stop = rt2x00mac_stop,
    .add_interface = rt2x00mac_add_interface,
    .remove_interface = rt2x00mac_remove_interface,
    .config = rt2x00mac_config,
    .configure_filter = rt2x00mac_configure_filter,
    .set_tim = rt2x00mac_set_tim,
    .set_key = rt2x00mac_set_key,
    .sw_scan_start = rt2x00mac_sw_scan_start,
    .sw_scan_complete = rt2x00mac_sw_scan_complete,
    .get_stats = rt2x00mac_get_stats,
    .bss_info_changed = rt2x00mac_bss_info_changed,
    .conf_tx = rt73usb_conf_tx,
    .get_tsf = rt73usb_get_tsf,
    .rfkill_poll = rt2x00mac_rfkill_poll,
    .flush = rt2x00mac_flush,
    .set_antenna = rt2x00mac_set_antenna,
    .get_antenna = rt2x00mac_get_antenna,
    .get_ringparam = rt2x00mac_get_ringparam,
    .tx_frames_pending = rt2x00mac_tx_frames_pending,
};

static const struct net_device_opsieee80211_dataif_ops = {        .ndo_open               = ieee80211_open,        .ndo_stop               = ieee80211_stop,        .ndo_uninit             = ieee80211_uninit,        .ndo_start_xmit         = ieee80211_subif_start_xmit,        .ndo_set_rx_mode        = ieee80211_set_multicast_list,        .ndo_change_mtu         = ieee80211_change_mtu,       .ndo_set_mac_address    = ieee80211_change_mac,       .ndo_select_queue       = ieee80211_netdev_select_queue,};

