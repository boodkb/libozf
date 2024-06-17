#include "catch.hpp"
#include "test_utils.h"

#include <details/utils/decode.h>

using namespace ozf::details;

TEST_CASE("decode1", "Utils")
{
    SECTION("Empty")
    {
        const int encryption_depth = 0;
        const uint8_t key = 0;
        std::vector<char> buffer;
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer.empty());
    }

    SECTION("Case1")
    {
        const int encryption_depth = 14;
        const uint8_t key = 207;
        const std::vector<char> decrypted = from_hex("7c6e000000004000010036040000");

        std::vector<char> buffer = from_hex("807712c0f66a781e042160bf2e11");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case2")
    {
        const int encryption_depth = 4;
        const uint8_t key = 207;
        const std::vector<char> decrypted = from_hex("f131a407");

        std::vector<char> buffer = from_hex("0d28b6c7");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case3")
    {
        const int encryption_depth = 40;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("280000004a0f00003913000001000800000000007ae5250100000000000000000001000000010000");

        std::vector<char> buffer = from_hex("aea39c4acafbc2a8b6b8e045b99ba47bf7e486dceccef81231b486a39c4a80f4c2a98fabe044b89b");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case4")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("a3fd7b00");

        std::vector<char> buffer = from_hex("255ee74a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case5")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("84b86e00");

        std::vector<char> buffer = from_hex("021bf24a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case6")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("7b967800");

        std::vector<char> buffer = from_hex("fd35e44a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case7")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("d06b7a00");

        std::vector<char> buffer = from_hex("56c8e64a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case8")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("06ec7a00");

        std::vector<char> buffer = from_hex("804fe64a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case9")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("b3137b00");

        std::vector<char> buffer = from_hex("35b0e74a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case10")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("113f7b00");

        std::vector<char> buffer = from_hex("979ce74a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case11")
    {
        const int encryption_depth = 1024;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("0e0608007788170008068f00318792008bc7960029461500a2470f0096898c001f498d009bbe560061c8cd00080a4e00a78a16008c678a002b484f002748d000904b4a008c98cf00998d52003c87ce008f140500b8d1cd00b4cf930032674f000a09d10020698e009ba89300a167130017271000a0a55600a7f7d0003268cb0047a6960038641a00b9e79900996851007d3b480047abca001f324e00aba2220098a8d100dba891003885580056494c0059698e00f2bd3a005b6853001a328f00cf68110026282d008feaca005f480e00cf6a4c001827d10090e59b0095280800dc8c520064888f00efad4c004e6acb0075a15800c9490f004b4b8d0007052d00b5f9e900bad1f400d08b8900ccacc900b0d3b2001a346d00bac27600dd8a1800234dee003f8aea00b0edb7008f382a0047a8b00068cab3006a89540085c8f0006a661700192eb10073a7ee001427ee009d492c00224aae0022496f00a7a8ad0093a9ec0066686d006488b1005d4733009c683100ceaaab008d6a6b005169af002d67b0008d8aad004e4a6b00bdd97a0058300b005134300053130800236873005369ef0006046f00cf6832009b8c7300da907000e3a873009caa720064683100648d720025483100c94b4600e5d4d100f1efd500f1f6f50048394900e1daee000a08b000e4a422002967ef00cd6b6800c1350b00eecd9400edceb300e9edb4003288ab00887bca008e7b8900a0d45c0077a13200898bee00ce7b8800881a270098bf770091e9b700b0d254000a11ee008ce8e900b53e47006da276008f4c670031663800cc562e004a59ae00cd9ba800c9bbee004a56ce006b8fcf004c1b2800718637009a8a360034877400e48f30008778ed00c29bc90040388d00433a6b004455ee006a93eb008868aa0083d4ce0042194a00b9170500bc3a28008cd4b100897bac00ecab370070ad9100e4e8980069b3cc0067b1b1003834b100cc5b49008cd699002037d10086d9e9001d37ed00f7c56700fada6b007e3b6800f5c14c00aaa4360094f4ba009ed579000f1791001118d10092f6ca0072b7f0000d186f001117b10091f7e900f9d0500073b1780015170c003795960035551700a35710009e9892001d598d002d584d002b59cb00945a4e003d98c9003676540029788f0097b89200a27615001c3714003676cf009d785100a8b8cf00e6b893005f58520065788e005b775300d57715002638300064571300d478500099380c0065988e005879cc00ca580e004f5a8d0018192b00d39a8e00cebbc90070751800a05830002c58b00020587100a5b8b000a0b8f000657870005a98ae005f58300097773300d4b9b200927972005e78b2002b79ab009a9aac005a5a6b002b7774005a79ed00d67830006b7734002b5736003378ea00d27a6a003797ac008c9beb008d5c6700");

        std::vector<char> buffer = from_hex("88a5944af77cd5a887ad6f45891c3e7b7c2310dcbf6dc81393f389a30ac30cf4dde102ab7bfbee9bcdb33ae48ed6d82b7a9927b40ac4164aabbc8da8a8e3304528d0e67b7b7c49dc0fa68f130d3348a3135e85f47a7942ab548a2b9b9e1cb8e48cd5472bfd7abfb41d0b0f4a2193d1a8988cf045183efa7b501356dca4431613761210a3a42e9af47b4f16ab792de99bd140bfe4c1775c2bc2217fb42d01be4a185c13a854037145801ef47ba1adcadccf425313c309bca3c722d3f4d89a00ab2f2da99b8a53dae409365c2b825b3fb449c9d04a98d313a81f4e7b452db3a47b2b68d4dcf2a35213de19caa3d2204bf4b709d7ab290cb79be7307ae481d9bb2b68ead8b43c72684a507f4ba84307294508481e7bedd0ebdc2ce9ab13ec3e9ea3bf076ef4fd2265ab50a80f9b2343dde4c174262bb5d982b4ec2ac84a053c32a8e5cdf745a1b51d7b844368dc820c3313acfdaaa3be002ef4e0e1e0ab47ed159b3fd21be4e0b4fb2bb99b80b4dbe4af4a1c9cf3a841014b4535f1c77ba68d29dcbb4c6d13bc3e2ba3d200ebf47f71f5abb875b39bfd4fc7e4d5cf9e2bfe7b42b4d5ca734a86f0ada840c3d2452317df7b2d74f6dc7583ae13ad1ef4a3f822b1f4a625fdabc50d899b6530b1e46308472b2cfce4b47755694ac8cd8ba86e710e45b2931c7b1340a4dcbf4c3213fcdfeea35d7f8bf42c651bab0d8b0b9b459643e4b4543d2b5568fbb408d8154a20209ea8f80ad2453110427b399f0edc1e31fa13a90bf1a30da337f4727adbabea54569b20931ee433e2d12bb0b147b409effb4ab192faa843fdce45f2c2027b3a7f2edc5f9033137be248a3f7c54ff48eb3a7ab91c38f9b36f1c1e4b25be22b399c01b401db714a426f0ba8cf936d45fba1c77bb3b168dcfcb83613b9dc2ca31f9e4ef480b1c5ab5952bd9b1041dfe40a08272b54689db46a08ab4af05953a86b437845d128607b905537dcae1f6c13fdefcfa3109c19f4e29f5eab669c519bb14c1ae47119f12b27c95ab4f898f44a75358ea8250fd6452c6f167b6931ffdc993c4c1320ac57a30ebc4af4b01f7fabed5dd79bbd6c46e4172b7f2b24c361b4f512e44a95e3cea8b83e76458dcebb7b54b396dc08b34f132ced0ba3b112cdf4e9f144ab741ff69b91e33ee4b0aac22bf46bbeb4111b0e4a2282d7a8939cf4458eed637b6a9cd7dc3e931213d70c15a3c312d2f4a7d001abbb32eb9b790ce2e4a0e4a62bb94422b452dbcc4a19cccea8ea336e45e0e2607b3dbc88dcd971501329adada34fd00ef40c1346ab9030a09b0c23c7e4aa84262bfd4b40b4231b2c4a204c32a8ead39045e203027ba8bcb6dc015cee13e50d34a30e33f2f49cd03dabcb3c139b36e15be4dc86fd2bf66445b4dcda714a568cf2a8e4dcd44593cc9a7bc49c6cdc4451b71306232aa310d16bf44ff4e8ab");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case12")
    {
        const int encryption_depth = 16;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("78daed57bd6be348149f4ec542e01654");

        std::vector<char> buffer = from_hex("fe79711d3d9f21e09b34ae80fa7bba2f");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case13")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("227c0000");

        std::vector<char> buffer = from_hex("a4df9c4a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case14")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("677e0000");

        std::vector<char> buffer = from_hex("e1dd9c4a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case15")
    {
        const int encryption_depth = 16;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("78daed94bf6f9b4014c7d93a448aaa48");

        std::vector<char> buffer = from_hex("fe7971de3f9b59e89b6c397ffc110633");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case16")
    {
        const int encryption_depth = 4;
        const uint8_t key = 89;
        const std::vector<char> decrypted = from_hex("677e0000");

        std::vector<char> buffer = from_hex("e1dd9c4a");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case17")
    {
        const int encryption_depth = 4;
        const uint8_t key = 7;
        const std::vector<char> decrypted = from_hex("62e5c258");

        std::vector<char> buffer = from_hex("56b488a0");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case18")
    {
        const int encryption_depth = 14;
        const uint8_t key = 148;
        const std::vector<char> decrypted = from_hex("41a9000000004000010036040000");

        std::vector<char> buffer = from_hex("8077d785bb2fbde3cbe62d84f3d6");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case19")
    {
        const int encryption_depth = 4;
        const uint8_t key = 148;
        const std::vector<char> decrypted = from_hex("251b79ba");

        std::vector<char> buffer = from_hex("e4c5ae3f");
        decode1(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }
}

TEST_CASE("decode4", "OzfUtils")
{
    SECTION("Empty")
    {
        const int encryption_depth = 0;
        const uint8_t key = 0;
        std::vector<char> buffer;
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer.empty());
    }

    SECTION("Case1")
    {
        const int encryption_depth = 40;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("28000000001000000010000001000800000000000000000100000000000000000001000000010000");

        std::vector<char> buffer = from_hex("2b739575e09e3a7abacba7c1170e69fbddcfdbb62d2fbce78dbc24188d5990831e2becde2ca6ece5");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case2")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("218c1200");

        std::vector<char> buffer = from_hex("22290327");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case3")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("98d80c00");

        std::vector<char> buffer = from_hex("9b2a6cc6");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case4")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("66661000");

        std::vector<char> buffer = from_hex("657f9865");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case5")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("ef551100");

        std::vector<char> buffer = from_hex("ec63a0ea");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case6")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("c6a91100");

        std::vector<char> buffer = from_hex("c5c837b1");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case7")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("a3c71100");

        std::vector<char> buffer = from_hex("a0347870");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case8")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("dcf11100");

        std::vector<char> buffer = from_hex("df6b17f0");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case9")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("ad871200");

        std::vector<char> buffer = from_hex("ae445c74");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case10")
    {
        const int encryption_depth = 28;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("78daedc1310d000000c320ff8afbcec70214000000f06e056170e2e9");

        std::vector<char> buffer = from_hex("7b5e38a32d6f1e6e388440b6af089d8792089a462262aab2f55f6c7b");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case11")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("f9030000");

        std::vector<char> buffer = from_hex("fa057f4a");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case12")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("14040000");

        std::vector<char> buffer = from_hex("176bdcb0");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case13")
    {
        const int encryption_depth = 28;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("78daedc1310d000000c320ff8afbcec70214000000f06e056170e2e9");

        std::vector<char> buffer = from_hex("7b5e38a32d6f1e6e388440b6af089d8792089a462262aab2f55f6c7b");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case14")
    {
        const int encryption_depth = 4;
        const uint8_t key = 159;
        const std::vector<char> decrypted = from_hex("14040000");

        std::vector<char> buffer = from_hex("176bdcb0");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case15")
    {
        const int encryption_depth = 40;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("28000000b29f0100b0fb000001000800000000006050b19800000000000000000001000000010000");

        std::vector<char> buffer = from_hex("2b617934f85b69c27cab4c0f2ff23f9dc0f21402cadf046797d1dbb241cc635c92f3a3a733aac8a9");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case16")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("8f9e8d3500000000");

        std::vector<char> buffer = from_hex("8c4210140cd9c464");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case17")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("ddffd82b00000000");

        std::vector<char> buffer = from_hex("deab2277d28e1ca2");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case18")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("7eb61b3300000000");

        std::vector<char> buffer = from_hex("7d6f8bb153482404");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case19")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("dd63d53400000000");

        std::vector<char> buffer = from_hex("de377b1dee589470");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case20")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("692a5e3500000000");

        std::vector<char> buffer = from_hex("6a223d75d577d8b9");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case21")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("318b853500000000");

        std::vector<char> buffer = from_hex("324293de3460dccb");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case22")
    {
        const int encryption_depth = 8;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("5ccd8c3500000000");

        std::vector<char> buffer = from_hex("5f1e93276e54a940");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case23")
    {
        const int encryption_depth = 1024;
        const uint8_t key = 74;
        const std::vector<char> decrypted = from_hex("000000003890e800b018100088d89800a8e0a000a8d8a00068986800c098700040684800a8f8d80008286000f8d8a000d8d8d8004898a000c0706000082040002870a000f8e0a800f8a0680090e89800c0d0e800b0f8c00028402800a0a0a00098a05000b0b0b000c88868005858580078788800a8c0e0008878400050505000a0e0a000a8d8a8008090a000e05840002028200090c89000a8a8a800a8f8a80090b8d800f8b0b800f868100068a87800f8807000b8e8b80038485800e0e8e800a0f8a000385838006078600090c09000d8f8f80098c0a0002870b80060a0a80080a8d000f858580038080800b8b8900088b88800c0c0c000e048380040484000a8e8a8000858a00068481000f8a0a80050989000c0f0c00088c8b000787878009898980040707000d0d0d00098b0d000e87048006898c80098f8b800f8e8e800f89898003840380050280800d0d8e8004878b000f0f8f0004878980010101000b0b8a000909890000048a000d880700080c0a000b8c0700070a8e000b0d8a000f8d0c800f8d8e000d068480068c8680068886800f89078005890c0007070700080a0800080b07800d8a0600078a07800d850380070b0a00078d0780078c8780078c07800b0e8b00078b8780098b0b80070809000f868680078b8a000f848480000409000c0d090007098700088a0880058785800e8f8e80040604000b0d8f000f8f8f800b0f8b0006060600020508000d0d0c800e8706800e0f8e000f8c8c800a8e0a800c8f0c8006868680098502000a0e0a800f8f0b800b0c09000e0887800e8e8e800a0d8a0004088a000f8c89000f8b0800080c88000e068480060c0b00098f0b00060b8a8003880d0004848480068a8a000c0a8800080786800405060006098d000c8c8c800b8b8b8006090c80030384000e0e0e00058a0a000b0e8a000f870280098c8f80050705000b8f8b8003880a000b0c89800c8e8f8009008080080c080002828280040a0f8005848300098d0a0003878b000d090780050586000f888800050604800b84840005088b8006848400070b87000f0d0a00058b0f80058707800b8d8b80058282800c8884800c0d8f8000808280070b0700038608000204870002040680080b8800030483000d870600098a0b800d0a0780080808000c8b088008098b00098d898006808080090a87800a0e8a800c0a8a00060789000f0f0f00098e8a800d0705000f8909800d8f0e000f0f8f8007888980020609800f8787000b0f8d00080b0800098d09800f8784800f0888000f8a0780070b0900018000000b8a8700088888800d8f8d800385038000038a000f890900000000000ffffff00fbdfa700bcfcbc00a7fca700a6dfa700f9ffff009cfbbc00de533e00c3dffb00fc5d5d00b3ffd300e55e4600a9ffa900b1ffb100b6ffb600abdfa700");

        std::vector<char> buffer = from_hex("0359a2a1eb836dbb4c15e381694c7f08c9af488aaf4497fa9084c7e5fd914d6eb768185d5aac95b78a1b474bd397235bce44c57b7848beb33a01d4faf7d8c7124d00038cfdd3bd7d4f9ffb4bc06ddc5b56d5f2a1559209d4014617a526fd079aacbebae0163ed3534fcefeeacd9fd7e6c127dd51823e8b365090ac8dfd996c1bae963912ecae56a6be7c9893979f8f2a763af01a3b66d08701b45d82b16db41a848d229b3f8bec96173b8c1641f1984f5ac1eef5bcb91721bdfbf824afb7ff701d8f7d90428c69fed21c358e8600fc70d622fd98659c9a26ba1858559ec161940b9f65259c799f7680270dbf50fa00c334decd9fd4fcb2bfeb13ac3ca2d5eac32d681d1f0b3e37b90d01d1091dfd45f537d5fec668bb670337544c4e5707993cd1467d00ceefe4f5ca664b3c4b0c91c7ac461f8e799d2ed5b1a4c5a01dc5b4ac262d053e7d9d5a5f170251bc5db1465acf94ca6716ba4991b78a284f13b15b6e6e1109793653d5730af506a113f61568cb9bc2477f02f089ec5976496473d7741a0b053fda489cf6554a52464a5394c6f801469d2c2f274853511235bf897f53aaa21eaf8facf4f7438193413fd26decd0d1f27910f2a51f275bcbf0cca9f2f96d2249995224da6fa2438fe15b82ea34e2d86d7acf10004469da0b7bef4008a30e0842ca0fbfb49d948c4e8ff7eec3f2a432291df006a59e8fe134f8b6fdefeb43ede838b0b9fa1437fe62d881a958ff0b40a55d5d336ca42102f4f768f36e88b0ab250f67445892e14f5e66a06b27e9d8cea57ae28d5bdb21f95a801f02f3dfc0a8638c93f488688790fd86cbb00309b987f557c81904261f2b9e6dea8414539b190aa1c596dc562a19be54e1c8f8fdd96154545cd815c6df4ab038318a458396b6efb768f8fe7b4457dc69e6f194d50f50898d177d30790cbba2b93deaf1f3d02231405bb08e28def17b36ed26dc88a287d683e04973e06c2cb0221ef692e62159a4177851635951c8c34ef6a46e2bf6a284f27635cc1ee9ed91e18cefc7712b6c1eee20994ccad2901920a953b55b6eab994109420d71dc0d0662323884300011c3e45e66f8698ad2930bafb5c7c0cb34d19e1adc1cbcab8676cce338ca446cd0dfc0e7f4dfbb171f77b23aae4fe7cba54bef152d9c903e90c093f78f0eeb16b32192d9a278762e709b44b01f8baa8f3158b63f182a7876b18c774a16e727beac3b06be6a4d10e7508b03ae33faf72c1fd6f2d4fc306dd44fca9fdd0c24e280e95babbdab0be812998ef09aa90ba2d3de6cb8fc56189ab7b0fb379315df01eda652c17cb4cc40f11c9966a5e6ba288b8c21f0eb21757b474e0ad9ace40add4b63e605b7fcf2000fbcc481711953ea7002867468b49212059191de792dbb8f316cf588b437e6d60626517b820ecb5baf0f4f9f6b70bd866156396378acc101");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case24")
    {
        const int encryption_depth = 247;
        const uint8_t key = 71;
        const std::vector<char> decrypted = from_hex("78dacd56318bdb30180d841aed812c1eae86844c85f8c26d81ea2f74f21fc8d05248238fc135cd4da27ba75b6f52161fdcdad58bff456ef560248f92a82cf952b84ed2b7f40db2313c4b7adff71e5fd77b823e47bfa46ed077d4682179d77bffe0a4a4ca4b54e64a08e5cfefb11052e74daea579f1e727862fa4d2cad085f0e6d3e1fce20a7ffea69e71f787e110fefce5214adddd0711fcf91f2e08951597c216c15fbff327537b34d7c236813f9f7c291143a6f861fb53c2abd40a10767f7ca985700508d2dff0a39904d49f9093fcdb8001fd4f57f26a8080fea7cfefc7da0f35f0e7e3bb17295e034007d4ff18ad25607f72a9d712");

        std::vector<char> buffer = from_hex("7a7f9a376c5df10c0b9612c2fd6da337c878131c7ac9d11a2c1660a2ecf62c48632cadbac86928bdb6e95deca0ebead38539864d6df554980798b66d6030c8f7ad11e469ee1229a7fb4166550efb487f3db1fac47c2a4ac6077d596204c7bc902204a7733703bb8e8bb511d6960a964556b59ab043fe8a1cf873705146c9519751aa7a0fc5c3f48f83527ae83e1baa49b7ceebc809cc28a4bc524a5461d8fa320bbc12a705c2f8770853e978c17e731964d08812b5099f69f921928f38df09735ba6cfe4c7e7494074b3c2bcf9ca012b65a7788a1068c8f4b81c3263309f9919f5eb5803007cf80a2f9e3e016a33b7fdd954d1c268f5ed");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case25")
    {
        const int encryption_depth = 247;
        const uint8_t key = 135;
        const std::vector<char> decrypted = from_hex("78dacd57bd8e9c30108e8464cd13d0a448b3f4cc53246f9007c8d57788361c3aa5dbf4aef206aefc02575ce32214f7204bb1322db6020bec2eac0d03ba9532cd9819d030f3cd9f4b7886c256b680e79cdbcaa439e4a921f3eaea1995a96a9b16a9adc9bc9a3ed7c69a866de61f41645bcdc121a7f96eba83434f8a3d57ddc1a16fb11c30f5f2e1e0d2cb25fb98c360d8a557bc9cf75ff1b3c0a9677a29fee783535fd7f7cc8131d89ef78cf2f92e47026f8c38b8625b333e16cce40894da681c635beb722c98c9913caa955230aef7a9a119fbc859814ce1b8be278eced488b48c4598ea9b9aa3c4bfc52942c6caf6a737a64080195355");

        std::vector<char> buffer = from_hex("7b68d46bfbb9ef2427065cc90e367e85d59adb826abf10450ca0947db01e1681ee19e76be18ede13d4bf3d9084906237ab13ead0eae0c52972903ebadadabf3f1f7a53e287ccecafaf1e1f2584d378ba59b19b06291afd3e472bf0ff0b46c769871643a0aaabb31a49948751d44eb1c4a85fd9dc0e980bfa3e0618aa29065280bd7fc649552a93ae5cd1c83403505fda1349d55f186e189ebc805507e021994ef5229d18ec415bd15e9efa09ef2d0b9eaa2b3e107e4492e77cb415328f84502ab5790ca2e835e6ecf1ce49130d8c1df91883968a5d22d2738fd36034981d76d963a82e5e2131c98ff793816e9eef5a728a34102093375a");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case26")
    {
        const int encryption_depth = 247;
        const uint8_t key = 119;
        const std::vector<char> decrypted = from_hex("78dacd56314fdb401446423d798f4484588284cb1abb6b10de40dd3a41764bb8f292f3683b518250644606ff018f66c9c0d281a18b07bc2175630a5bc910d91eef8e9e5d9cd8e74072f5d237f80dc997e7ef7bdf7b2fd818080303c7d8100497a01811a0c264f340c4088d0c6784018ee318df073cf818618211c52df2af1b87075f0e84d0a1c2014fcab57104f088a77c92737fcb3337203cf493bfdae73da0d9153b3c048490c42414facbfc388575ea0706179ee14f738bab7f8cfe341f72e91f5782abfd2bfc377a75fed1ff596e4f442efe45edd31c08220f8372ef69168e61adfa86c6e5df0a7fcef961f54718d6ea3fda7ea8e5");

        std::vector<char> buffer = from_hex("7ba6c297e755ad5cb94045670f6c134710800bbd76acc592045c3b7fb73b2838a4351436c230356f8b14bb8d4ff5213c50a250e4ec02aa31000e4a40bab71e98138bec8954de69055393b85160f08e44dd5fb1d0881b92524bac25bf6c168dcac3655b0b69a8a118362ccbcfd271554327e823619afe21e11be5168e43cf362b5ca5928471d6947cb078e48b7d200c63f18ba485f389b4832753f3c70310a3dae273f3e829a861d1270fe2f976560955d30c9940c4635b59bce301fcf3971798d1153f4a74d36bc038f60e8e2d97d49481abb3449bf11b19fe2f362a8732edc03455c81e57078e92e53acb452eb3dafc23a727e59f5b61");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case27")
    {
        const int encryption_depth = 247;
        const uint8_t key = 30;
        const std::vector<char> decrypted = from_hex("78dae5973f6fe23018c63b796226aa3a1c03b03190ac41f55875bb09b17b8894c9ab0951a910f2eae1a69bca88a793baf00558d86ece94ac1e10ca07b8d781141a381a9f4fba4af74858e0f0c3af9ff7f51ff2dc40d84b05cfff5c1c536ec35b8bdb0dcf85b0fa011a122bff64a4326cc3bbea15ffc3f12989ed78dfbefefe6e3d51e3fae32730e5a9118e8528e75fc0843043ff19d10194f0f836310b7fb752e0e11b3c5f8c0c0b68194b7c841921666eef96ed53386cd1fa99a7344f51f3eb295cb31a009e8a30d4233b3353589b9d3182101b2df4c8a111ac71e612361a2de6c9ad390cd3ce4267306f24dd31c0412e4d46a6d84311");

        std::vector<char> buffer = from_hex("7ab3c08b807d9a5b873d00795493ce3582aa5144e25dfccb02c99c41a37df6b2e360de6ca3f2e349b4294f2390b865a4c274034a102d08db42248cf82da141a8a16cfbd95d4662d0a97d590b3d3975efda250c99bffcbdbbe2806c400a7b2de0127697441e365c504ffe03ca6a3d80d450b9813c4cf217c856185dc117a7fdfe7af8df8f2d3d895cd99fc7b0bf8d3c8ad4bc0dfb5aeb9c1006b81162f4cc82d4cae8c13ceac7fe6e3818da60c6ac74f72c30054fd3cfc38d28f3c0dec65719509c6c5ce694ba0762f89d830003981e1edf2184bef0bad7635e4fbdc41e4412663ee9f4b23b4e2d1f3c1c169a5be0c52bf87d539a197355");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case28")
    {
        const int encryption_depth = 247;
        const uint8_t key = 7;
        const std::vector<char> decrypted = from_hex("78daedd7a16ac3401c06f0a93031dd526a22bab98adc6c4a4ef60d42fc8983537f7b4d4b3b46c93b4c6536668399bd404cdd7454622342b807d8e5c8525a06bb5bcd60f71347cdd7ef4b38d10af19304c34e942426345aec8b494449ecdc638044684800a0e288103a7e5cdfdc514e10af00b04e5816cf135f16b36852ac174bca11a2ee5c33dc1773ba54ab995ced6bae3e2d4ec75fabf51e59e0f362528a9dde6a353c3b2dbed52eee8643e23b71fabb628037d60d8f16a6c55d5816237947d4f0c8372856e19210be5af6174c7e0f08d3f0a4d8a7e315931f2b83e1c7f0b32af605e80f978630372cee0d61e69a15f78e61f36ce7a2");

        std::vector<char> buffer = from_hex("7a10fe87233ba43d2a48740255e8c706c35b1a47d9e611f24beda7114ec86a2d7a7fa1540d73b5960c4fe98dd4e4631108edca94b4fdd20f461a843630ee4832dce1d2fd1c08c9e1123281b2576972306fbcf7e10125ac6d5da98699ade348fe3953e07792c2430cca3dd3c3f6e203b8e28bc60a112bd8f0cb74835d4caf4fd50b8f426a22aa6f42fe3770110827807d9ab535de7361b5f8547d3f20ad4d833078cf13d50fd53a7f54d3f4bdbc898e8875f592ca645c25dac7a78e86a44821d64fa5553c56afb6c6acdf0bf146dca41335a27114e8443500d34b1fdac9d982eb3b0b5d9d68b3fbd3c2122f9a883bf4b30a74e6b409bc72");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case29")
    {
        const int encryption_depth = 247;
        const uint8_t key = 126;
        const std::vector<char> decrypted = from_hex("78daedd62f8fc23018c7f1539733b533d8bd81cd20578547cd4c4e5c42263084900986aae5b19ca6a2082ee1356070f7124e572c4b7dd9f8b31082e0ee27c6eef88ac77db2a64b9b1af3c3e492e6d6fc3e99d006f2118d24e06d8f12c8cfa98b786189415e1229680389ad9005c8152368031541de6498af3610f202fc81b6596fc1f5a307a0f57e037af4026ad873d0a317b81c51047e3f6af5fa13ea71d0db36fb0ff001d1051f30ffdd2fc908c433b216f4a2592f210f3e7f9efee9ff8ee755a23c4f5c1575eaaa6c7851c1480df9b96dd97afd9515c54e6bcff37435dfd234f57dbf9ef1e0fb7d3089d343f178fcbaadcb8f85aeeb");

        std::vector<char> buffer = from_hex("7b3eeea369e1c66b52e3aae65e7c6fcd1d2e93f61ae3e8c4beefa7a7b07ce5fd41236cb07c8ae702e4c0f94f7fe6d082783f12d52e1a406f271ca4dc0d916bc62258d3dfd516820c4b8568e59b5c00436177d5616ddafc5d96accf3ce249f07faf1d5680c6d548848f876e3b5b1740ea461af18da462da4c6652f270048b2dd2705f773639f72995f848cdac5df10591fa6b34b4553e21217bbddf8a12fe84d2299bd220bc7b328e5b920de0aa9eaca38ba44ddeb853885cfb01e7ef09dae426248a75c617e36250fcb2f8b86e22bbf750c1d81150c72cd90a6b9ebdb9b63ae9cc51570cca27be93816aa9a872529ac89588985538a148");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case30")
    {
        const int encryption_depth = 188;
        const uint8_t key = 154;
        const std::vector<char> decrypted = from_hex("78dafbf265148c82514032b80a01e46a5f6b0d01e4eabf100d0103653fa5fe071b3163c60c0ab477586f23dfff54d04f91fbaf52187ed6e72060a0d2cf175608203ff4478b9051300a46c1281805a360a4020730e800b6061c567f8283d5e8a0101d3840c1313028bad4f8e9d3e93740606868082477d618d5d4d41819c1c894ec478f32aa526a6020e5180c7c8082701515b1d9d2d24d1bc381a47438c369fb37f670f2cd6931957031950f584003047c200a340c3e0000f8918d7f");

        std::vector<char> buffer = from_hex("7b593707bb05941ada8146aa13b228fe90ae1d15e69843dfde1448d196141d06caae667c424d9f9128c819787027e66f865dcce9677424c6057ae93c9ad6a5aa26dfc820a9fcf2a41a9d7f7fdac156ad6ceb58fc221e287d89adb6f6db0206c61f33f84bf61f55fb0460edf6a30133a693d02e196846ff53177b877afbecfeeee32129667dfff789228c4aa88ff2a82af909a6c5acf295f64d59a09311da17c181308c22286f396cba7c52a69cf9e5297fbaee1a006c31e4f8cedfd8");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case31")
    {
        const int encryption_depth = 172;
        const uint8_t key = 26;
        const std::vector<char> decrypted = from_hex("78dafbf265148c82910bae52a8df7a2d65faa32f0cacfd94fa7f06085ced21dfff20706e6dc740e9a7d4fd57290cc073d6039b7e58298cff8ed12264148c8251300a46c128180524020708e8e8f8e2b0fa1302ac460785e800aaf11804145d6afc74fa8da1a1e19b3760b2aec6c8c8a8a6064ea65465643cca4ea9810336a8c60f3010ae22d6b4317cb6b4349894b70f67386dff064e8a01810ac3074cd000051f88020d830e0000f1ae9c1e");

        std::vector<char> buffer = from_hex("7a415b3caf7fb8677547467ea20f81ae8d052293083bb159baa4c33b4d0ce86ca44127a01fdfa7ef105639756dd9fc81bc23f047007ae3abae509606c32f101b992bd292e40a448dceffcb6b0dcb5f85f2d7d4ed4d9b2d2b046beba7e8f3c2b71547c8f3978f048a88a08d4686fdd3b966f5f9df5422473a29f33b373de96d257a761d52bfda8a9c90e81fbce7b29f1c559f18eeb1882e8631fe69367be171c68c7d06c989956e3f2d457681");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }

    SECTION("Case32")
    {
        const int encryption_depth = 247;
        const uint8_t key = 190;
        const std::vector<char> decrypted = from_hex("78daed95a14fc34014c6a708667606450212d14d609aac6a097f41cd64c51232f11084344d33502fb89e234caf09a74866f60f6070fc099de4c4b29c2f6bba4d40dfbdcbce40c227ce5c7f69bf7bdf7dd5da42b910b976d03fffcfff751e5df8b6289df84b9195fc6308d0fc967c2ae6163c140534f3b762607100324d65333f14c3293f81b552ebc68d722084052f9547f15a5ce6fcf129e2fbb144d1e6798c6220b6ac12885916b82410917c249f09ed94c0199f204408904ef080e5b3a247fa9ff23cf82975fe558287391b7f754df24371cbf22335a2f872ce0718625590fca998f1df1f9d53e787251fe04dfce88cd804d890bfaa");

        std::vector<char> buffer = from_hex("7b6473d29e0eb39b8c2ab68c94d102d4dda04a5c748ee8c392e517effe8882fd4060d685084aad3ef38a24ede16f70a52d6ca4a4208e56cc341f40838e62bc7e41d77cb22624461d0ea4ee45f7ee77d22ab97f065e5dd03276b8646d918a0f8f0579e6bc4e30c830b5f078e19049410c436dded06b37b2db38e33fa56e5c2cab9131eaf15b4961ae0aef070dcfa565fef113b1d272d32cf381b93da97f225703e764f794050552101b10a6d28d99c39b5272c9294fa86b0603919c67649fda542acdd468c3545e93dce84db85e623c7dc167d1a7676a42e8f46afd660f22944ce273b4f301814b5bca9c2ae40423629767a4d2b2c61ac1");
        decode4(buffer.data(), encryption_depth, key);
        REQUIRE(buffer == decrypted);
    }
}

TEST_CASE("modifyKey")
{
    SECTION("Case1")
    {
        const uint8_t initial_key = 0x74;
        const int tile_data_size = 2264;
        const uint8_t expected = 0xb4;

        REQUIRE(modify_key(tile_data_size, initial_key) == expected);
    }

    SECTION("Case2")
    {
        const uint8_t initial_key = 0x4a;
        const int tile_data_size = 628;
        const uint8_t expected = 0x1a;

        REQUIRE(modify_key(tile_data_size, initial_key) == expected);
    }

    SECTION("Case3")
    {
        const uint8_t initial_key = 0x3d;
        const int tile_data_size = 2562;
        const uint8_t expected = 0x51;

        REQUIRE(modify_key(tile_data_size, initial_key) == expected);
    }

    SECTION("Case4")
    {
        const uint8_t initial_key = 0x9f;
        const int tile_data_size = 786;
        const uint8_t expected = 0xf3;

        REQUIRE(modify_key(tile_data_size, initial_key) == expected);
    }

    SECTION("Case5")
    {
        const uint8_t initial_key = 0x5c;
        const int tile_data_size = 1174;
        const uint8_t expected = 0xd0;

        REQUIRE(modify_key(tile_data_size, initial_key) == expected);
    }
}
