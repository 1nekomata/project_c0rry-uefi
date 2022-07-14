/* TODO:
    ~~- Set Display Mode through GOP~~ done
    - List Files
    - Load and Execute Selected (or default) File/Kernel
    - Memory stuff
*/



#include "uefi/uefi.h"

int main(int argc, char *argv[]){
    efi_status_t status;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    efi_gop_mode_info_t *info = NULL;
    uintn_t isiz = sizeof(efi_gop_mode_info_t), currentMode, i;

    status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    if(!EFI_ERROR(status) && gop){
        status = gop->QueryMode(gop, gop->Mode ? gop->Mode->Mode : 0, &isiz, &info);

        if(status == EFI_NOT_STARTED || !gop->Mode){
            status = gop->SetMode(gop, 0);
            ST->ConOut->Reset(ST->ConOut, 0);
            ST->StdErr->Reset(ST->StdErr, 0);
        }

        if(EFI_ERROR(status)){
            fprintf(stderr, "Failed to get current Video Mode!\n");
            return 1;
        }
        
        //This for was stolen from the posix-uefi vidmodes example
        //and modified to reduce the amount of info displayed
        currentMode = gop->Mode->Mode;
        for (i = 0; i < gop->Mode->MaxMode; i++) {
            status = gop->QueryMode(gop, i, &isiz, &info);
            if(EFI_ERROR(status) || info->PixelFormat > PixelBitMask) continue;
            printf(" %c%3d. %4d x%4d\n",
                i == currentMode ? '*' : ' ', i,
                info->HorizontalResolution,
                info->VerticalResolution);
        }

        printf("Please select the desired Video Mode... ");
        const char_t mode = getchar();
        if(mode > (const char_t)-1){
            gop->SetMode(gop, atoi(&mode));
            status = ST->ConOut->SetAttribute(ST->ConOut, EFI_TEXT_ATTR(ST->ConOut->Mode->Attribute & 0x0F, EFI_BACKGROUND_BLACK));
            if(EFI_ERROR(status)){
                fprintf(stderr, "Failed to set Attribute of ConOut!\n");
                return 1;
            }
            status = ST->ConOut->SetMode(ST->ConOut, 0);
            if(EFI_ERROR(status)){
                fprintf(stderr, "Failed to set mode of ConOut!\n");
            }
        }
        printf("\n");
        printf("Good Morning, Mothafucka!\n");

    } else {
        fprintf(stderr, "Failed to get Graphics Output Protocol!\n");
    }

    return 0;
}
