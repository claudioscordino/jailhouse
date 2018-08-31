#ifndef INMATE_ETH_H
#define INMATE_ETH_H

/* Taken using "sudo lspci -nn" */
#define ETH_VENDORID		0x8086
#define ETH_DEVICEID		0x1533

/* TODO: check */
#define ETH_IRQ_VECTOR		42

#define IGB_DEFAULT_RXD		256
#define IGB_DEFAULT_TXD		256

#define E1000_RCTL     0x00100  /* RX Control - RW */

#define E1000_RXDCTL(_n)  ((_n) < 4 ? (0x02828 + ((_n) * 0x100)) \
                                    : (0x0C028 + ((_n) * 0x40)))
/* Receive Descriptor - Advanced */
union e1000_adv_rx_desc {
        struct {
                u64 pkt_addr;             /* Packet buffer address */
                u64 hdr_addr;             /* Header buffer address */
        } read;
        struct {
                struct {
                        struct {
                                u16 pkt_info;   /* RSS type, Packet type */
                                u16 hdr_info;   /* Split Head, buf len */
                        } lo_dword;
                        union {
                                u32 rss;          /* RSS Hash */
                                struct {
                                        u16 ip_id;    /* IP id */
                                        u16 csum;     /* Packet Checksum */
                                } csum_ip;
                        } hi_dword;
                } lower;
                struct {
                        u32 status_error;     /* ext status/error */
                        u16 length;           /* Packet length */
                        u16 vlan;             /* VLAN tag */
                } upper;
        } wb;  /* writeback */
};


struct eth_device {
	void *bar_addr;
};



#define print(...)          printk("Ethernet: " __VA_ARGS__)


#endif /* INMATE_ETH_H */