#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*print_binary(int number);
int		bin_to_int(char *str, int len);
int		parse_packet(char *str);

int	main(void)
{
	char hex[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
//	char	*str = "C0015000016115A2E0802F182340";
//	char	*str = "A0016C880162017C3686B18A3D4780";
//	char	*str = "8A004A801A8002F478";
//	char	*str = "620080001611562C8802118E34";
//	char	*str = "EE00D40C823060";
//	char	*str = "38006F45291200";
//	char	*str = "D2FE28";
//

	char	*str = "2056FA18025A00A4F52AB13FAB6CDA779E1B2012DB003301006A35C7D882200C43289F07A5A192D200C1BC011969BA4A485E63D8FE4CC80480C00D500010F8991E23A8803104A3C425967260020E551DC01D98B5FEF33D5C044C0928053296CDAFCB8D4BDAA611F256DE7B945220080244BE59EE7D0A5D0E6545C0268A7126564732552F003194400B10031C00C002819C00B50034400A70039C009401A114009201500C00B00100D00354300254008200609000D39BB5868C01E9A649C5D9C4A8CC6016CC9B4229F3399629A0C3005E797A5040C016A00DD40010B8E508615000213112294749B8D67EC45F63A980233D8BCF1DC44FAC017914993D42C9000282CB9D4A776233B4BF361F2F9F6659CE5764EB9A3E9007ED3B7B6896C0159F9D1EE76B3FFEF4B8FCF3B88019316E51DA181802B400A8CFCC127E60935D7B10078C01F8B50B20E1803D1FA21C6F300661AC678946008C918E002A72A0F27D82DB802B239A63BAEEA9C6395D98A001A9234EA620026D1AE5CA60A900A4B335A4F815C01A800021B1AE2E4441006A0A47686AE01449CB5534929FF567B9587C6A214C6212ACBF53F9A8E7D3CFF0B136FD061401091719BC5330E5474000D887B24162013CC7EDDCDD8E5E77E53AF128B1276D0F980292DA0CD004A7798EEEC672A7A6008C953F8BD7F781ED00395317AF0726E3402100625F3D9CB18B546E2FC9C65D1C20020E4C36460392F7683004A77DB3DB00527B5A85E06F253442014A00010A8F9106108002190B61E4750004262BC7587E801674EB0CCF1025716A054AD47080467A00B864AD2D4B193E92B4B52C64F27BFB05200C165A38DDF8D5A009C9C2463030802879EB55AB8010396069C413005FC01098EDD0A63B742852402B74DF7FDFE8368037700043E2FC2C8CA00087C518990C0C015C00542726C13936392A4633D8F1802532E5801E84FDF34FCA1487D367EF9A7E50A43E90";
	char	*bits;
	char	*aux;
	int	num;
	char	*num_bin;
	size_t	i;

	bits = 0;
	num_bin = 0;
	bits = malloc(sizeof(char) * 10000);
	aux = bits;
	bzero(bits, 10000);
	i = 0;
	while (*str)
	{
		num = strchr(hex, *str) - hex;
		num_bin = print_binary(num);
		strncpy(aux, num_bin, 4);
		free(num_bin);
		aux += 4;
		str++;
	}
	printf("%s\n", bits);
	printf("total version %i\n", parse_packet(bits));
	free(bits);
}

int	parse_packet(char *str)
{
	int	version;
	int	packet_version;
	int	len_type_id;
	int	subpackets;
	int	subp_len;
	size_t	num;
	int	i;

	i = 0;
	while (str && *str)
	{
		num = 0;
		len_type_id = -1;
		subpackets = 0;
		subp_len = 0;
		version = bin_to_int(str, 3);
		str += 3;
		packet_version = bin_to_int(str, 3);
		str += 3;
		if (packet_version != 4)
		{
			len_type_id = bin_to_int(str, 1);
			str++;
			if (len_type_id)
			{
				subpackets = bin_to_int(str, 11);
				str += 11;
			}
			else
			{
				subp_len = bin_to_int(str, 15);
				str += 15;
			}
		}
		else
		{
			while (str && *str == '1')
			{
				str++;
				num = (num << 4) | bin_to_int(str, 4);
				str += 4;
			}
			str++;
			num = num << 4 | bin_to_int(str, 4);
			str += 4;
		}
		i += version;
		printf("version %i, packet v %i, %i, %i, %i\n", version, packet_version, len_type_id, subpackets, subp_len);
	}
	return (i);
}

char	*print_binary(int number)
{
	int		i;
	char	*n;

	i = 3;
	n = malloc(sizeof(char) * 4);
	while (i >= 0)
	{
		n[3 - i] = ((number >> i) & 1) + 48;
		i--;
	}
	return (n);
}

int	bin_to_int(char *str, int len)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (str && str[i] && i < len)
	{
		num = (((str[i] - 48) & 1)) | num << 1;
		i++;
	}
	return (num);
}

